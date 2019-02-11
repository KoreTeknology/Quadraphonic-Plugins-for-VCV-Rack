# Quadraphonic-Plugins-for-VCV-Rack

> This page is in progress, please, come back soon !

### TASKLIST before first release
- [x] Step 1: Setup home page and documentation structure
- [ ] Step 2: Uploading first code parts in documentation
- [ ] Step 3: Making available the module files and builds

---

This is an educational project, based on the creation of a set of **Modules** for VCV Rack, Open-source virtual modular synthesizer  https://github.com/VCVRack/Rack .


The initial project was to create a serie of Modules, used for quadraphonic performances. The concept was developped 20 years ago but only few hardware prototypes were made at this time. The objective is to recreate theses concepts in a virtual environment (VCV Rack) and add some extra features. Here is a list of needed "components":

- **QuadraTrack**, a Single Mono Input track to 4 outputs with controls and options (or 4x4 matrix...)
- **QuadraMaster**, An master output section with 4 audio inputs/outputs with effects, limiter and options
- **QuadraEngine**, a 4 tracks sequencer, recorder/player, audio/midi from files, with 4 audio channel and 16 Midi channel

---

I can consider this project as a WIP (work in progress), files will be updated on major upgrades without deadline until the complete documentation will be published. it start with a pdf format for printing purpose and a set of files, organized by chapters.

The complete work of documentation is released under Open document license and the modules files is release under Open source license. 

The final documentation will have several sections like:
- **How to plan your Module Development**, from idea to project planning
- **How to make a new Module**, an advanced tutorial on the Quadratrack mixer development
- **How to use/test your new module in VCV Rack**, a complete manual of using VCV Rack and testing modules process

---

## Modules Builds

These plugins will be available for Windows, Apple and Linux computers. 

| Date | Title |
| --- | --- |
| **2019-02-19** | Module *QuadraTrack 0.2b* - for **Rack v0.6.2** |

---

## Overview and short description of the modules

### QuadraTrack Module: Type MIXER
this module is intended to recieve a single mono channel and distribute it to 4 outputs. The user may manipulate de sound space with manual controls (can be assigned to external Midi CC) OR internal automation control thru CV Levels. Mutes and CV levels give more precision and creativity to any quadriphonic scenery design. [Read the specifications](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Documentation/quadratrack.md)

| **Status:** *In progress* | **Title:** *0.2b* |
| --- | --- |

### QuadraMaster Module: Type AUDIO
this module is intended to recieve 4 mono channels and apply various treatments and effects to 4 audio outputs, ready to be connected to the device outputs. The user may set the parameters, accordingly to the performance project and room size of any quadriphonic scenery. [Read the specifications](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Documentation/quadramaster.md)

| **Status:** *In progress* | **Title:** *none* |
| --- | --- |

### QuadraEngine Module: Type SEQUENCER
this module is intended to Record/Play/import/export a specific files package. It contains 4 audio files, 1 configuration text file and a midi file. The objectives here is to record live performances and replay them in order to modifiy in real time the quadrphonic motions . [Read the specifications](https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Documentation/quadraengine.md)

| **Status:** *In progress* | **Title:** *none* |
| --- | --- |

---

Mockups in progress, previous research of UI Design and user experience.
<p align="center">
<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Mockups/protoUI1.jpg" width=90%>
</p>

---

## Authors

* **Uriel Deveaud** - *Initial work* - [Kore Teknology](https://github.com/KoreTeknology)

Please, feel free to contact me, and/or discuss further development or ideas for these plugins, thanks ;)


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
