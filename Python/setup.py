# -*- coding: utf-8 -*-
import setuptools

setuptools.setup(
    name="TheColdWorldConfigEditer",
    version="0.0.1",
    author="TheColdWorld",
    author_email="thecoldworld@foxmail.com",
    description="A solution that stores settings in a file",
    long_description="A solution that stores settings in a file",
    install_requires=[     
        'copy'
    ],
    long_description_content_type="text",
    url="https://github.com/TheColdWorld/TheColdWorldConfigEditer",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
)
