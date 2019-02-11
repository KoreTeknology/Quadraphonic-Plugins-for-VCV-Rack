# Quadraphonic-Plugins-for-VCV-Rack

> This page is in progress, please, come back soon !

This is an educational project, based on the creation of a set of **Modules** for VCV Rack, Open-source virtual modular synthesizer  https://github.com/VCVRack/Rack .


The initial project was to create a serie of Modules, used for quadraphonic performances. The concept was developped 20 yars ago but only few hardware prototypes were made at this time. The objective is to recreate theses concepts in a virtual environment (VCV Rack) and add some extra features. Here is a list of needed "components":

- **QuadraTrack**, a Single Mono Input track to 4 outputs with controls and options (or 4x4 matrix...)
- **QuadraMaster**, An master output section with 4 audio inputs/outputs with effects, limiter and options
- **QuadraPlayer**, a 4 tracks sequencer, recorder/player, audio/midi from files, with 4 audio channel and 16 Midi channel

I can consider this project as a WIP (work in progress), files will be updated on major upgrades without deadline until the complete documentation will be published. it start with a pdf format for printing purpose and a set of files, organized by chapters.

The complete work of documentation is released under Open document license and the modules files is release under Open source license. 

The final documentation will have several sections like:
- **How to plan your Module Development**, from idea to project planning
- **How to make a new Module**, an advanced tutorial on the Quadratrack mixer development
- **How to use/test your new module in VCV Rack**, a complete manual of using VCV Rack and testing modules process

## Modules Builds

These plugins will be available for Windows, Apple and Linux computers. 
**2019-02-19**: 0.2b, the latest version is for Rack v0.6.2


<p align="center">
<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Com/header_mod1.jpg" width=100%>
</p>




## Overview and description of the modules

### QuadraTrack Module: Type MIXER

Setup | Details
------------ | -------------
INPUT SECTION | 1 audio input jack, input knob, vu meter, CV control over VCA-IN
MATRIX SECTION | 1x4 multiplexer with gain knob, CV control, mute switch
OUTPUT SECTION | 4 audio output jack 

<br>


### TASKLIST

- [x] Step 1: Setup of development environment
- [x] Step 2: Implementing UI code and variables
- [ ] Step 3: Implementing DSP code
- [ ] Step 4: Compiling for all plateforms
- [ ] Step 5: Publishing the tutorial and the plugins...

<br>

Mockups in progress, previous research of UI Design and user experience.
<p align="center">
<img src="https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack/blob/master/Project/Mockups/protoUI1.jpg" width=90%>
</p>





### Instructions ###

* **Open** ... !
* **Select** ....
* **Press** ... et voila !


## Authors

* **Uriel Deveaud** - *Initial work* - [Kore Teknology](https://github.com/KoreTeknology)

Please, feel free to contact me, and/or discuss further development or ideas for these plugins, thanks ;)

## License

This project is licensed under the BSD License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* This work is dedicated to all VCV users ;)



```c++
if (isAwesome){
  return true
}
```
