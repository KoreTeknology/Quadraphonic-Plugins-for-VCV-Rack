//***********************************************************************************************
//
// QuadraphonicStudio Modules for VCV Rack by Uriel deveaud 
// Module name: Main cpp for Quadraphonics modules
// https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack
//  
//***********************************************************************************************

#include "Quadraphonics.hpp"

Plugin *plugin;

void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	// Add all Models defined throughout the plugin
	p->addModel(modelQS_Diffuser);
	p->addModel(modelQS_Merger);
	p->addModel(modelQS_AudioOutputs);
	p->addModel(modelQS_Vumeter);
	p->addModel(modelQS_Blank4);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
