import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist

class YoubotAutopilot(Node):
    def __init__(self):
        super().__init__('youbot_autopilot')
        
        # --- CONFIGURAZIONE ---
        self.distanza_sicurezza = 0.8
        self.velocita_lineare = 0.5
        self.velocita_rotazione = 0.6
        
        # --- DEFINIZIONE QoS "SENSOR DATA" ---
        # Questo permette di ascoltare sia "Reliable" che "Best Effort"
        qos_profile = QoSProfile(
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=10
        )
        
        # Sottoscrizione al Lidar con il nuovo QoS
        self.subscription = self.create_subscription(
            LaserScan,
            '/scan_webots',
            self.scan_callback,
            qos_profile)  # <--- Usiamo il profilo qui
            
        self.publisher_ = self.create_publisher(Twist, '/rover_twist', 10)
        self.get_logger().info('Youbot Autopilot avviato. In attesa di dati laser...')

    def scan_callback(self, msg):
        # Creiamo il messaggio di movimento
        cmd = Twist()
        
        # 
        # Analizziamo i dati del Lidar.
        # Il Lidar dello Youbot ha solitamente lo zero di fronte o sul retro a seconda del montaggio.
        # drive.py inverte l'array (list(reversed(ranges_))), quindi assumiamo una mappatura standard.
        
        # Prendiamo solo i valori validi (escludiamo infinito e 0.0 che drive.py usa per i punti ciechi)
        valid_ranges = [r for r in msg.ranges if r > 0.05 and r < msg.range_max]
        
        if not valid_ranges:
            # Se non vediamo nulla o siamo ciechi, fermiamoci per sicurezza
            self.publisher_.publish(cmd)
            return

        # Dividiamo la vista in settori.
        # Assumiamo che l'array rappresenti una scansione da destra a sinistra (o viceversa).
        # Prendiamo la porzione centrale per vedere cosa c'è DAVANTI.
        mid_index = len(msg.ranges) // 2
        window_size = len(msg.ranges) // 10  # Guardiamo il 10% centrale
        
        # Estraiamo il settore frontale
        start = mid_index - window_size
        end = mid_index + window_size
        
        # Protezione indici array
        front_ranges = msg.ranges[start:end]
        
        # Filtriamo i valori nulli (0.0) che nel tuo drive.py indicano zone morte
        front_ranges_clean = [r for r in front_ranges if r > 0.05]
        
        distanza_minima_frontale = float('inf')
        if front_ranges_clean:
            distanza_minima_frontale = min(front_ranges_clean)
            
        self.get_logger().info(f'Distanza ostacolo frontale: {distanza_minima_frontale:.2f}m')

        # --- LOGICA DI MOVIMENTO ---
        
        if distanza_minima_frontale < self.distanza_sicurezza:
            # OSTACOLO RILEVATO: Ruota sul posto
            # Poiché è un robot omnidirezionale (Mecanum), potremmo anche traslare di lato,
            # ma ruotare è più sicuro per i sensori frontali.
            cmd.linear.x = 0.0
            cmd.angular.z = self.velocita_rotazione
            self.get_logger().info('Ostacolo! Ruoto a sinistra.')
        else:
            # VIA LIBERA: Vai avanti
            cmd.linear.x = self.velocita_lineare
            cmd.angular.z = 0.0
            self.get_logger().info('Avanti tutta.')

        # Pubblica il comando
        self.publisher_.publish(cmd)

def main(args=None):
    rclpy.init(args=args)
    youbot_pilot = YoubotAutopilot()
    
    try:
        rclpy.spin(youbot_pilot)
    except KeyboardInterrupt:
        pass
    finally:
        # Ferma il robot alla chiusura
        stop_cmd = Twist()
        youbot_pilot.publisher_.publish(stop_cmd)
        youbot_pilot.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
