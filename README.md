[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://opensource.org/licenses/MIT)
## Overview

This is an API to control Beaglebone's GPIO and an application to exemplify the use of API on controling cpu usage of Jessie (Debian for Beaglebone) system's processes. The API was developed in C++ and can be used to: **export**, **unexport**, **get direction**, **set direction**, **set value** and **get value** of _pins_. The example catches cpu usage on file <b>/proc/stat</b> and catches cpu usage of processes on file <b>/proc/[pid]/stat</b>.    

## Installation

Using this application requires <b>Boost Filesystem Library</b>: 

<b>Debian Based</b>: `sudo apt-get install libboost-all-dev`

<b>Fedora</b>: `yum install boost-devel`

## Usage

Check <a href="http://viniciuscampos.me/GPIO-API/documentation/html/index.html" target="_blank">documentation</a>. 

## Example

```#include <iostream>
#include "GPIOSystem.h"
#include "Pin.h"

int main(void) {
	Pin redled {"P9_14", GPIOSystem::Direction::IN, GPIOSystem::Value::LOW};
  	return 0;
}
```

## Team

| [![Vinicius Campos](https://avatars.githubusercontent.com/Vinihcampos?s=100)](https://github.com/Vinihcampos) | [![Vitor Rodrigues Greati](https://avatarhttp://greati.github.io/GPIO-API/documentation/html/index.htmls.githubusercontent.com/greati?s=100)](http://greati.github.io)
---|---
[Vinícius Campos](https://github.com/Vinihcampos) | [Vitor Greati](http://greati.github.io)

