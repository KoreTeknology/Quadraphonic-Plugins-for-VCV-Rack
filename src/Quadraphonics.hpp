//***********************************************************************************************
//
// QuadraphonicStudio Modules for VCV Rack by Uriel deveaud 
// Module name: Main hpp for Quadraphonics modules
// https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack
//  
//***********************************************************************************************

#include "rack.hpp"

using namespace rack;

// Forward-declare the Plugin, defined in Template.cpp
extern Plugin *plugin;

// Forward-declare each Model, defined in each module source file
extern Model *modelQS_Diffuser;
extern Model *modelQS_Merger;
extern Model *modelQS_AudioOutputs;
extern Model *modelQS_Vumeter;
extern Model *modelQS_Blank4;

// COMPONENTS

// Corners themed screws
struct QS_Screw : SVGScrew {
	QS_Screw() {
		sw->svg = SVG::load(assetPlugin(plugin, "res/QS_Components/QS_screw.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

// Custom Switch push button
struct BtnMuteSwitch : SVGSwitch, ToggleSwitch {
    BtnMuteSwitch() {
        addFrame(SVG::load(assetPlugin(plugin, "res/QS_Components/QS_mute_off.svg")));
        addFrame(SVG::load(assetPlugin(plugin, "res/QS_Components/QS_mute_on.svg")));
    }
};

// custom knob
struct QS_potsmall : SVGKnob {
    QS_potsmall() {
		minAngle = -0.82 * M_PI;
		maxAngle = 0.82 * M_PI;
        setSVG(SVG::load(assetPlugin(plugin, "res/QS_Components/QS_potsmall.svg")));
    }
};

// Custom linear fader
struct QS_Fader : SVGFader {
	QS_Fader() { // 15x74px > 213
		Vec margin = Vec(4, 4);
		maxHandlePos = Vec(-1.5, -8).plus(margin);
		minHandlePos = Vec(-1.5, 111).plus(margin); //213-8 = 195px ... 147-8=139
		background->svg = SVG::load(assetPlugin(plugin,"res/QS_Components/QS_fader_line.svg"));
		background->wrap();
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
		handle->svg = SVG::load(assetPlugin(plugin,"res/QS_Components/QS_fader_black.svg"));
		handle->wrap();
	}
};

// Custom Vu meter lights box
template <typename BASE>
 struct VuMeter : BASE {
 	VuMeter() {
 		this->box.size = Vec(6, 6);
		 this->bgColor = nvgRGB(0x14, 0x14, 0x14);
 	}
 };

struct OrangeLight : GrayModuleLightWidget {
	OrangeLight() {
		addBaseColor(COLOR_CYAN);
	}
};

struct BlueLight : GrayModuleLightWidget {
	BlueLight() {
		addBaseColor(COLOR_PURPLE);
	}
};

// custom Color Jack ports
struct QS_jackgoldPort : SVGPort {
	QS_jackgoldPort() {
		setSVG(SVG::load(assetPlugin(plugin,"res/QS_Components/QS_jack_gold.svg")));
	}
};

struct QS_jackblackPort : SVGPort {
	QS_jackblackPort() {
		setSVG(SVG::load(assetPlugin(plugin,"res/QS_Components/QS_jack_black.svg")));
	}
};

struct QS_jackredPort : SVGPort {
	QS_jackredPort() {
		setSVG(SVG::load(assetPlugin(plugin,"res/QS_Components/QS_jack_red.svg")));
	}
};

struct QS_jacksilverPort : SVGPort {
	QS_jacksilverPort() {
		setSVG(SVG::load(assetPlugin(plugin,"res/QS_Components/QS_jack_silver.svg")));
	}
};

struct QS_cvsilverPort : SVGPort {
	QS_cvsilverPort() {
		setSVG(SVG::load(assetPlugin(plugin,"res/QS_Components/QS_cv_silver.svg")));
	}
};

// Custom visual helper for CV input to knob over layer
struct QS_AutomatedPot : TransparentWidget {
	float d;
	float *gainX ;
	int *affich;

	QS_AutomatedPot() {
	}
	
	void draw(NVGcontext *vg) override {
		if (*affich==1) {
		float xx = d*sin(-(*gainX*0.17+0.15)*M_PI) ;
		float yy = d*cos((*gainX*0.17+0.15)*M_PI) ;

			nvgBeginPath(vg);
			nvgCircle(vg, 0,0, d);
			// Transparent background
			nvgFillColor(vg, nvgRGBA(0x00, 0x00, 0x00, 0x00));
			nvgFill(vg);
			
			nvgStrokeWidth(vg,1.2);
			// Red line
			nvgStrokeColor(vg, nvgRGBA(0xff, 0x00, 0x00, 0xff));

			{
				nvgBeginPath(vg);
				nvgMoveTo(vg, 0,0);
				nvgLineTo(vg, xx,yy);
				nvgClosePath(vg);
			}
			nvgStroke(vg);
		}

	}
};
