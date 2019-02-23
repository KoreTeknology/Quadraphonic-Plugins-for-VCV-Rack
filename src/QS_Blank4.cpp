//***********************************************************************************************
//
// QuadraphonicStudio Modules for VCV Rack by Uriel deveaud 
// Module name: Merger
// https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack
//  
//***********************************************************************************************

#include "Quadraphonics.hpp"


// Variables definition
struct QS_Blank4 : Module {
	enum ParamIds {	
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	QS_Blank4() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}

	void step() override;
};

// All inputs from 4 quadraphonic audio tracks = 16 inputs
void QS_Blank4::step() {

}

	

// UI Panel
struct QS_Blank4Widget : ModuleWidget {
	
	QS_Blank4Widget(QS_Blank4 *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/QS_blankpanel4.svg")));

	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelQS_Blank4 = Model::create<QS_Blank4, QS_Blank4Widget>("Quadraphonics", "QS_Blank4", ":: BlankPanel 4HP", UTILITY_TAG);
