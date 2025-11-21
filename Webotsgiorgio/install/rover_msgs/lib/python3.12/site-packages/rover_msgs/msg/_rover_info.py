# generated from rosidl_generator_py/resource/_idl.py.em
# with input from rover_msgs:msg/RoverInfo.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

# Member 'footprint'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RoverInfo(type):
    """Metaclass of message 'RoverInfo'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('rover_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'rover_msgs.msg.RoverInfo')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__rover_info
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__rover_info
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__rover_info
            cls._TYPE_SUPPORT = module.type_support_msg__msg__rover_info
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__rover_info

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RoverInfo(metaclass=Metaclass_RoverInfo):
    """Message class 'RoverInfo'."""

    __slots__ = [
        '_footprint',
        '_safety_margin',
        '_min_lin_vel',
        '_max_lin_vel',
        '_min_ang_vel',
        '_max_ang_vel',
        '_max_lin_acc',
        '_max_ang_acc',
        '_max_cen_acc',
        '_lin_resolution',
        '_ang_resolution',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'footprint': 'double[6]',
        'safety_margin': 'double',
        'min_lin_vel': 'double',
        'max_lin_vel': 'double',
        'min_ang_vel': 'double',
        'max_ang_vel': 'double',
        'max_lin_acc': 'double',
        'max_ang_acc': 'double',
        'max_cen_acc': 'double',
        'lin_resolution': 'double',
        'ang_resolution': 'double',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 6),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        if 'footprint' not in kwargs:
            self.footprint = numpy.zeros(6, dtype=numpy.float64)
        else:
            self.footprint = numpy.array(kwargs.get('footprint'), dtype=numpy.float64)
            assert self.footprint.shape == (6, )
        self.safety_margin = kwargs.get('safety_margin', float())
        self.min_lin_vel = kwargs.get('min_lin_vel', float())
        self.max_lin_vel = kwargs.get('max_lin_vel', float())
        self.min_ang_vel = kwargs.get('min_ang_vel', float())
        self.max_ang_vel = kwargs.get('max_ang_vel', float())
        self.max_lin_acc = kwargs.get('max_lin_acc', float())
        self.max_ang_acc = kwargs.get('max_ang_acc', float())
        self.max_cen_acc = kwargs.get('max_cen_acc', float())
        self.lin_resolution = kwargs.get('lin_resolution', float())
        self.ang_resolution = kwargs.get('ang_resolution', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if any(self.footprint != other.footprint):
            return False
        if self.safety_margin != other.safety_margin:
            return False
        if self.min_lin_vel != other.min_lin_vel:
            return False
        if self.max_lin_vel != other.max_lin_vel:
            return False
        if self.min_ang_vel != other.min_ang_vel:
            return False
        if self.max_ang_vel != other.max_ang_vel:
            return False
        if self.max_lin_acc != other.max_lin_acc:
            return False
        if self.max_ang_acc != other.max_ang_acc:
            return False
        if self.max_cen_acc != other.max_cen_acc:
            return False
        if self.lin_resolution != other.lin_resolution:
            return False
        if self.ang_resolution != other.ang_resolution:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def footprint(self):
        """Message field 'footprint'."""
        return self._footprint

    @footprint.setter
    def footprint(self, value):
        if self._check_fields:
            if isinstance(value, numpy.ndarray):
                assert value.dtype == numpy.float64, \
                    "The 'footprint' numpy.ndarray() must have the dtype of 'numpy.float64'"
                assert value.size == 6, \
                    "The 'footprint' numpy.ndarray() must have a size of 6"
                self._footprint = value
                return
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 6 and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'footprint' field must be a set or sequence with length 6 and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._footprint = numpy.array(value, dtype=numpy.float64)

    @builtins.property
    def safety_margin(self):
        """Message field 'safety_margin'."""
        return self._safety_margin

    @safety_margin.setter
    def safety_margin(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'safety_margin' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'safety_margin' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._safety_margin = value

    @builtins.property
    def min_lin_vel(self):
        """Message field 'min_lin_vel'."""
        return self._min_lin_vel

    @min_lin_vel.setter
    def min_lin_vel(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'min_lin_vel' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'min_lin_vel' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._min_lin_vel = value

    @builtins.property
    def max_lin_vel(self):
        """Message field 'max_lin_vel'."""
        return self._max_lin_vel

    @max_lin_vel.setter
    def max_lin_vel(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'max_lin_vel' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_lin_vel' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_lin_vel = value

    @builtins.property
    def min_ang_vel(self):
        """Message field 'min_ang_vel'."""
        return self._min_ang_vel

    @min_ang_vel.setter
    def min_ang_vel(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'min_ang_vel' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'min_ang_vel' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._min_ang_vel = value

    @builtins.property
    def max_ang_vel(self):
        """Message field 'max_ang_vel'."""
        return self._max_ang_vel

    @max_ang_vel.setter
    def max_ang_vel(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'max_ang_vel' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_ang_vel' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_ang_vel = value

    @builtins.property
    def max_lin_acc(self):
        """Message field 'max_lin_acc'."""
        return self._max_lin_acc

    @max_lin_acc.setter
    def max_lin_acc(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'max_lin_acc' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_lin_acc' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_lin_acc = value

    @builtins.property
    def max_ang_acc(self):
        """Message field 'max_ang_acc'."""
        return self._max_ang_acc

    @max_ang_acc.setter
    def max_ang_acc(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'max_ang_acc' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_ang_acc' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_ang_acc = value

    @builtins.property
    def max_cen_acc(self):
        """Message field 'max_cen_acc'."""
        return self._max_cen_acc

    @max_cen_acc.setter
    def max_cen_acc(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'max_cen_acc' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'max_cen_acc' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._max_cen_acc = value

    @builtins.property
    def lin_resolution(self):
        """Message field 'lin_resolution'."""
        return self._lin_resolution

    @lin_resolution.setter
    def lin_resolution(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'lin_resolution' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'lin_resolution' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._lin_resolution = value

    @builtins.property
    def ang_resolution(self):
        """Message field 'ang_resolution'."""
        return self._ang_resolution

    @ang_resolution.setter
    def ang_resolution(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'ang_resolution' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'ang_resolution' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._ang_resolution = value
