# Quadraphonic-Plugins-for-VCV-Rack

<img src="https://img.shields.io/badge/Quadraphonics Modules-for VCV%20Rack-orange.svg" alt="Name" /> <img src="https://img.shields.io/badge/Uriel Deveaud-2019-blue.svg" />  <img src="https://img.shields.io/badge/C++-Coding-purple.svg" />    <img src="https://img.shields.io/badge/Virtual-Audio Rack-lightgrey.svg" />

<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Com/presentation_s1.jpg" width=100%>

The aim of this project is to produce a serie of audio tools to perform real time multi-channels mixing and "Surround" Automation sequencing. This is an Educational and Research project, based on the creation of a set of **Quadraphonics Modules** for VCV Rack, the **Awesome** Open-source Virtual Modular Synthesizer Software for Windows, MacOS and Linux computers, visit the [VCV Rack Official Website](https://github.com/VCVRack/Rack).

[Read also the Tutorials Section](https://github.com/KoreTeknology/Tutorial-How-to-create-modules-for-VCV-Rack) (always in progress!)

## Latest Builds

| Date | Title | Downloads |
| --- | --- | --- |
| **2019-02-22** | Module *Quadraphonics* - for **VCV Rack v0.6x** - Win10/MacOS/Linux |[0.6.3](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/releases) |

---

<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Com/cablesQuad2.jpg" width=100%>

---

## Overview of the modules 

### QuadraTrack Module: Type MIXER
This module is intended to recieve a single mono channel and distribute it to 4 outputs. The user may manipulate de sound space with manual controls (can be assigned to external Midi CC) OR internal automation control thru CV Levels. Mutes and CV levels give more precision and creativity to any quadriphonic scenery design. [Read the specifications](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Documentation/quadratrack.md)

| **Status:** *In progress* | **Title:** *MK1* |
| --- | --- |

### QuadraMaster Module: Type AUDIO
this module is intended to recieve 4 mono channels and apply various treatments and effects to 4 audio outputs, ready to be connected to the device outputs. The user may set the parameters, accordingly to the performance project and room size of any quadriphonic scenery. [Read the specifications](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Documentation/quadramaster.md)

| **Status:** *In progress* | **Title:** *MK1* |
| --- | --- |

### QuadraEngine Module: Type SEQUENCER
this module is intended to Record/Play/import/export a specific files package. It contains 4 audio files, 1 configuration text file and a midi file. The objectives here is to record live performances and replay them in order to modifiy in real time the quadrphonic motions . [Read the specifications](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Documentation/quadraengine.md)

| **Status:** *Stopped* | **Title:** *none* |
| --- | --- |


## Development Plans

At the moment, i am focusing on re-formating the module serie, by UI design, but also by new features. The MKII serie will be improved at various levels, here are some early preview sketches, mockups and plans.

<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Com/preview_mk2.jpg" width=100%>

Also, the project includes a DIY hardware build. i dont have all the knowledge to build an analog system, so my idea is to build an exact copy of the virtual module on its visual aspect and ergonomy, but as a MIDI controller.
I will publish a documentation as soon as i start to build the device... stay tuned !

---

## Author

* **Uriel Deveaud** - *Initial work* - [Kore Teknology](https://github.com/KoreTeknology) from 2001

<img src="https://img.shields.io/badge/Aktiv-25-9cf.svg" /> <img src="https://img.shields.io/badge/5-Viento-9cf.svg" /> <img src="https://img.shields.io/badge/Kore-Teknology-9cf.svg" />

Please, feel free to contact me, and/or discuss further developments or ideas for those plugins, thanks ;)
Collaboration projects are always welcome ;)

---

<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Com/pre2010.jpg" width=100%>


## History
The initial project was to create a serie of Modules, used for **real-time quadraphonic performances**. I developped my own concept 20 years ago, but only one hardware prototype was made at this time and it didn´t have a good looking, to be honest, even if it was working as expected.  
See 2002 Patent Document: https://patents.google.com/patent/FR2839601A1/en?oq=FR2839601A1

The objective is to recreate theses concepts in a virtual environment (VCV Rack) and add some extra features. Here is a list of needed "audio components":

- **QuadraMixer**, a matrix mixer with 4 inputs/outputs with controls and options
- **QuadraMaster**, An master output section with 4 audio inputs/outputs with effects, limiter and options
- **QuadraEngine**, a tracks sequencer, recorder/player, audio/midi from files, with 4 audio channels and 16 Midi channels

---

I can consider this project as a **WIP** (work in progress), files will be updated on major upgrades without deadline until the complete documentation will be published. The complete work of documentation is released under Open document license and the modules files is release under Open source license. 

The final documentation will cover several sections like:
- **How to plan your Module Development**, from idea to project planning
- **How to make a new Module**, an advanced tutorial on the Quadratrack mixer development
- **How to use/test your new module in VCV Rack**, a complete manual of using VCV Rack and testing modules process

#Important#
I am moving the documentation to this page: [Tutorials Section](https://github.com/KoreTeknology/Tutorial-How-to-create-modules-for-VCV-Rack)

---

## Translations

I would like to publish it in spanish and french as well, Please, feel free to contact me it you are interested ;)


## License

This project is licensed under the BSD License - see the [LICENSE.md](LICENSE.md) file for details


## Acknowledgments

* This work is dedicated to all VCV users ;)
* i will try to keep all types of codes as clear as possible using syntax highlighting and line referencing

```c++
if (isAwesome){
  return true
}
```
> This page is in progress, please, come back soon !

### TASKLIST before first release
- [x] Step 1: Setup home page and documentation structure
- [ ] Step 2: Uploading first code parts in documentation
- [ ] Step 3: Making available the module files and builds

---
