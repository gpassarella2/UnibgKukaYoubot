import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from sensor_msgs.msg import JointState
import sys
import select
import tty
import termios

# Velocità massime
BASE_LIN_SPEED = 0.4  # m/s
BASE_ANG_SPEED = 0.8  # rad/s
CAM_SPEED = 0.5       # rad/s

# Messaggio di istruzioni
msg = """
---------------------------
Controllo KUKA Youbot
---------------------------
Movimento Base:
   w
a  s  d
   x

q/e : ruota (ang. z)

Movimento Camera:
   i
j  k  l
   ,

w/x = avanti/indietro (lin. x)
a/d = sinistra/destra (lin. y)
q/e = rotazione sinistra/destra (ang. z)
s   = STOP BASE

i/, = tilt su/giù
j/l = pan sinistra/destra
k   = STOP CAMERA

(Rilascia il tasto per fermare il movimento)

CTRL-C per uscire
"""

# Mappatura tasti -> velocità base (vx, vy, vth)
key_map_base = {
    'w': (BASE_LIN_SPEED, 0.0, 0.0),
    'x': (-BASE_LIN_SPEED, 0.0, 0.0),
    'a': (0.0, BASE_LIN_SPEED, 0.0),
    'd': (0.0, -BASE_LIN_SPEED, 0.0),
    'q': (0.0, 0.0, BASE_ANG_SPEED),
    'e': (0.0, 0.0, -BASE_ANG_SPEED),
    's': (0.0, 0.0, 0.0)
}

# Mappatura tasti -> velocità camera (v_pan, v_tilt)
key_map_camera = {
    'i': (0.0, CAM_SPEED),
    ',': (0.0, -CAM_SPEED),
    'j': (CAM_SPEED, 0.0),
    'l': (-CAM_SPEED, 0.0),
    'k': (0.0, 0.0)
}

# Salva le impostazioni originali del terminale
old_attr = termios.tcgetattr(sys.stdin)

def getKey():
    """Legge un singolo tasto dal terminale senza aspettare Invio."""
    tty.setcbreak(sys.stdin.fileno())
    # Controlla se c'è input in arrivo, con un timeout di 0.1 secondi
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    # Ripristina le impostazioni del terminale
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)
    return key


class TeleopNode(Node):
    def __init__(self):
        super().__init__('youbot_teleop_keyboard')
        
        # --- Publishers ---
        # Publisher per il movimento della base
        self.base_pub = self.create_publisher(Twist, 'rover_twist', 10)
        
        # Publisher per il movimento della camera
        self.cam_pub = self.create_publisher(JointState, 'camera_vel', 10)
        
        # --- Messaggi ---
        self.base_twist = Twist()
        self.cam_joint = JointState()
        
        # Inizializza il messaggio JointState
        # Il driver si aspetta i nomi e le velocità in questo ordine
        self.cam_joint.name = ['pan_joint', 'tilt_joint']
        self.cam_joint.velocity = [0.0, 0.0] # [pan_vel, tilt_vel]

        # Stato attuale (per logica 'deadman's switch')
        self.current_base_vel = [0.0, 0.0, 0.0]
        self.current_cam_vel = [0.0, 0.0]

        self.get_logger().info(msg)
        
        # Timer principale per il loop di controllo
        self.timer = self.create_timer(0.1, self.control_loop)

    def control_loop(self):
        """Loop principale: legge i tasti e pubblica i comandi."""
        
        key = getKey()
        
        base_vel_updated = False
        cam_vel_updated = False

        if key in key_map_base:
            # Aggiorna velocità base
            self.current_base_vel = key_map_base[key]
            base_vel_updated = True
        
        if key in key_map_camera:
            # Aggiorna velocità camera
            self.current_cam_vel = key_map_camera[key]
            cam_vel_updated = True
        
        # Logica "Deadman's Switch" (interruttore a uomo morto):
        # Se nessun tasto è premuto (key == ''), o il tasto non è mappato,
        # resetta le velocità a zero.
        if key == '':
            if self.current_base_vel != [0.0, 0.0, 0.0]:
                self.current_base_vel = [0.0, 0.0, 0.0]
            if self.current_cam_vel != [0.0, 0.0]:
                self.current_cam_vel = [0.0, 0.0]
        elif not base_vel_updated and not cam_vel_updated and key != '\x03':
            # Tasto non valido (ma non CTRL-C)
            self.get_logger().warn(f"Tasto non valido: '{key}'")
            self.current_base_vel = [0.0, 0.0, 0.0]
            self.current_cam_vel = [0.0, 0.0]

        # Controlla per CTRL-C
        if (key == '\x03'):
            self.get_logger().info('Uscita richiesta (CTRL-C). Arresto...')
            # Pubblica un ultimo comando di stop prima di uscire
            self.stop_all_motion()
            self.publish_commands()
            # Ferma il nodo
            rclpy.shutdown()
            return

        # Pubblica i comandi
        self.publish_commands()

    def publish_commands(self):
        """Aggiorna i messaggi e li pubblica."""
        
        # --- Base ---
        self.base_twist.linear.x = float(self.current_base_vel[0])
        self.base_twist.linear.y = float(self.current_base_vel[1])
        self.base_twist.angular.z = float(self.current_base_vel[2])
        self.base_pub.publish(self.base_twist)

        # --- Camera ---
        self.cam_joint.velocity[0] = float(self.current_cam_vel[0]) # pan
        self.cam_joint.velocity[1] = float(self.current_cam_vel[1]) # tilt
        self.cam_joint.header.stamp = self.get_clock().now().to_msg()
        self.cam_pub.publish(self.cam_joint)

    def stop_all_motion(self):
        """Funzione di sicurezza per fermare tutto."""
        self.current_base_vel = [0.0, 0.0, 0.0]
        self.current_cam_vel = [0.0, 0.0]
        self.publish_commands()
        self.get_logger().info('Tutti i movimenti fermati.')


def main(args=None):
    rclpy.init(args=args)
    node = TeleopNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(f"Errore durante lo spin: {e}")
    finally:
        # Assicurati di fermare il robot e ripristinare il terminale
        node.stop_all_motion()
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()

if __name__ == '__main__':
    main()

