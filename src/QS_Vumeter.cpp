//***********************************************************************************************
//
// QuadraphonicStudio Modules for VCV Rack by Uriel deveaud 
// Module name: 5 vu-meters
// https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack
//  
//***********************************************************************************************

#include "Quadraphonics.hpp"
#include "dsp/digital.hpp"
#include "dsp/vumeter.hpp"

// Main definitions
struct QS_Vumeter : Module {
	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		AUDIO_INPUT,
        AUDIO1_INPUT,
        AUDIO2_INPUT,
        AUDIO3_INPUT,
        AUDIO4_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		METER_LIGHT_0,
		METER_LIGHT_1 = METER_LIGHT_0+5,
		METER_LIGHT_2 = METER_LIGHT_1+5,
		METER_LIGHT_3 = METER_LIGHT_2+5,
		METER_LIGHT_4 = METER_LIGHT_3+5,
		NUM_LIGHTS = METER_LIGHT_4+5
	};


	// Declare all params
	QS_Vumeter() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}

	// Features
	void step() override {
		
		// Vumeter
		float signal_in = inputs[AUDIO_INPUT].value;
        float signal_in1 = inputs[AUDIO1_INPUT].value;
        float signal_in2 = inputs[AUDIO2_INPUT].value;
        float signal_in3 = inputs[AUDIO3_INPUT].value;
        float signal_in4 = inputs[AUDIO4_INPUT].value;

		vuBar.dBInterval = 10;

		// loop for each meter
		for (int i = 0; i < 5; i++){
			vuBar.setValue(signal_in / 10.0f);
			lights[METER_LIGHT_0 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_in1 / 10.0f);
			lights[METER_LIGHT_1 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_in2 / 10.0f);
			lights[METER_LIGHT_2 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_in3 / 10.0f);
			lights[METER_LIGHT_3 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_in4 / 10.0f);
			lights[METER_LIGHT_4 + i].setBrightnessSmooth(vuBar.getBrightness(i));
		}
	}
	VUMeter vuBar;
};


// UI Panel
struct QS_VumeterWidget : ModuleWidget {
	Menu *createContextMenu() override;
	QS_VumeterWidget(QS_Vumeter *module) : ModuleWidget(module) {

		// original set of bg
		setPanel(SVG::load(assetPlugin(plugin, "res/bg_vumeter.svg")));

		// Input section
		addInput(Port::create<QS_jackgoldPort>(Vec(8, 27), Port::INPUT, module, QS_Vumeter::AUDIO_INPUT));
		addInput(Port::create<QS_jackgoldPort>(Vec(8, 100), Port::INPUT, module, QS_Vumeter::AUDIO1_INPUT));
		addInput(Port::create<QS_jackgoldPort>(Vec(8, 151), Port::INPUT, module, QS_Vumeter::AUDIO2_INPUT));
		addInput(Port::create<QS_jackgoldPort>(Vec(8, 204), Port::INPUT, module, QS_Vumeter::AUDIO3_INPUT));
		addInput(Port::create<QS_jackgoldPort>(Vec(8, 256), Port::INPUT, module, QS_Vumeter::AUDIO4_INPUT));
		
        // Vu meters
		static const float ledCol = 45;
        static const float offsetY = 8;
        static const float startY = 98;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY + offsetY * 0), module, QS_Vumeter::METER_LIGHT_1 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY + offsetY * 1), module, QS_Vumeter::METER_LIGHT_1 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 2), module, QS_Vumeter::METER_LIGHT_1 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 3), module, QS_Vumeter::METER_LIGHT_1 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 4), module, QS_Vumeter::METER_LIGHT_1 + 4));

        static const float startY2 = 151;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY2 + offsetY * 0), module, QS_Vumeter::METER_LIGHT_2 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY2 + offsetY * 1), module, QS_Vumeter::METER_LIGHT_2 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY2 + offsetY * 2), module, QS_Vumeter::METER_LIGHT_2 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY2 + offsetY * 3), module, QS_Vumeter::METER_LIGHT_2 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY2 + offsetY * 4), module, QS_Vumeter::METER_LIGHT_2 + 4));

        static const float startY3 = 202;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY3 + offsetY * 0), module, QS_Vumeter::METER_LIGHT_3 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY3 + offsetY * 1), module, QS_Vumeter::METER_LIGHT_3 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY3 + offsetY * 2), module, QS_Vumeter::METER_LIGHT_3 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY3 + offsetY * 3), module, QS_Vumeter::METER_LIGHT_3 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY3 + offsetY * 4), module, QS_Vumeter::METER_LIGHT_3 + 4));

        static const float startY4 = 254;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY4 + offsetY * 0), module, QS_Vumeter::METER_LIGHT_4 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY4 + offsetY * 1), module, QS_Vumeter::METER_LIGHT_4 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY4 + offsetY * 2), module, QS_Vumeter::METER_LIGHT_4 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY4 + offsetY * 3), module, QS_Vumeter::METER_LIGHT_4 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY4 + offsetY * 4), module, QS_Vumeter::METER_LIGHT_4 + 4));
        
        static const float startY5 = 24;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY5 + offsetY * 0), module, QS_Vumeter::METER_LIGHT_0 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY5 + offsetY * 1), module, QS_Vumeter::METER_LIGHT_0 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY5 + offsetY * 2), module, QS_Vumeter::METER_LIGHT_0 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY5 + offsetY * 3), module, QS_Vumeter::METER_LIGHT_0 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY5 + offsetY * 4), module, QS_Vumeter::METER_LIGHT_0 + 4));
	}
};


// integrated menu > Right Click Panel
Menu *QS_VumeterWidget::createContextMenu() {
	Menu *menu = ModuleWidget::createContextMenu();

	MenuLabel *spacerLabel = new MenuLabel();
	menu->addChild(spacerLabel);

    MenuLabel *modeLabel = new MenuLabel();
	modeLabel->text = "-------------- FEATURES:";
	menu->addChild(modeLabel);

	MenuLabel *modeLabel2 = new MenuLabel();
	modeLabel2->text = "5x mono Vu-meters";
	menu->addChild(modeLabel2);

	return menu;
}

// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelQS_Vumeter = Model::create<QS_Vumeter, QS_VumeterWidget>("Quadraphonics", "QS_Vumeter", ":: Vu Meters MKI", VISUAL_TAG, UTILITY_TAG);
