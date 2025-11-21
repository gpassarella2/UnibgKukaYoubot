from setuptools import find_packages
from setuptools import setup

setup(
    name='aurora_msgs',
    version='5.0.4',
    packages=find_packages(
        include=('aurora_msgs', 'aurora_msgs.*')),
)
