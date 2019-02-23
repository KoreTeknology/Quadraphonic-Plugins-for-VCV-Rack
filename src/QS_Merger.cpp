//***********************************************************************************************
//
// QuadraphonicStudio Modules for VCV Rack by Uriel deveaud 
// Module name: Quad Matrix Mixer QM-1200 MK1
// https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack
//  
//***********************************************************************************************

#include "Quadraphonics.hpp"
#include "dsp/digital.hpp"
#include "dsp/vumeter.hpp"

// Main definitions
struct QS_Merger : Module {
	enum ParamIds {
		// knob params for outputs
		OUTLEVEL1_PARAM,
		OUTLEVEL2_PARAM,
		OUTLEVEL3_PARAM,
		OUTLEVEL4_PARAM,
		// extra outputs
		OUTLEVEL_ST_PARAM,
		OUTLEVEL_ST2_PARAM,

		STOUTLEVEL_PARAM,

		// mute params for outputs
		MUTE1_BUTTON_PARAM,
		MUTE2_BUTTON_PARAM,
		MUTE3_BUTTON_PARAM,
		MUTE4_BUTTON_PARAM,

		// knob params for inputs by channel
		INLEVEL1_ABCD_PARAM,
		INLEVEL2_ABCD_PARAM,
		INLEVEL3_ABCD_PARAM,
		INLEVEL4_ABCD_PARAM,

		NUM_PARAMS
	};
	enum InputIds {
		// Channel 1
		AUDIO_CH1_INPUT_A,
		AUDIO_CH1_INPUT_B,
		AUDIO_CH1_INPUT_C,
		AUDIO_CH1_INPUT_D,
		// Channel 2
		AUDIO_CH2_INPUT_A,
		AUDIO_CH2_INPUT_B,
		AUDIO_CH2_INPUT_C,
		AUDIO_CH2_INPUT_D,
		// Channel 3
		AUDIO_CH3_INPUT_A,
		AUDIO_CH3_INPUT_B,
		AUDIO_CH3_INPUT_C,
		AUDIO_CH3_INPUT_D,
		// Channel 4
		AUDIO_CH4_INPUT_A,
		AUDIO_CH4_INPUT_B,
		AUDIO_CH4_INPUT_C,
		AUDIO_CH4_INPUT_D,
		// CV input to control outputs section
		CV_OUT1_INPUT,
		CV_OUT2_INPUT,
		CV_OUT3_INPUT,
		CV_OUT4_INPUT,

		NUM_INPUTS
	};
	enum OutputIds {
		// Main Output section
		AUDIO_OUTPUT,
		AUDIO2_OUTPUT,
		AUDIO3_OUTPUT,
		AUDIO4_OUTPUT,
		// bottom mixed mono outputs
		AUDIOL_OUTPUT,
		AUDIOR_OUTPUT,
		// 	top merged outputs
		AUDIO_AD_OUTPUT,
		AUDIO_BC_OUTPUT,

		NUM_OUTPUTS
	};
	enum LightIds {
		METER_LIGHT_AD,
		METER_LIGHT_BC = METER_LIGHT_AD+5,
		METER_LIGHT_1 = METER_LIGHT_BC+5,
		METER_LIGHT_2 = METER_LIGHT_1+5,
		METER_LIGHT_3 = METER_LIGHT_2+5,
		METER_LIGHT_4 = METER_LIGHT_3+5,
		NUM_LIGHTS = METER_LIGHT_4+5
	};

	float x = 0;
	float y = 0;
	int length = 0;

	float gain_gain2 ;
	int gain_affi2 ;
	float gain_gain3 ;
	int gain_affi3 ;
	float gain_gain4 ;
	int gain_affi4 ;
	float gain_gain5 ;
	int gain_affi5 ;

	QS_Merger() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}

	// Override
	void step() override{
		float cvo1 = 1.f;
		float cvo2 = 1.f;
		float cvo3 = 1.f;
		float cvo4 = 1.f;

		// IF a jack is connected to CV input
		if (inputs[CV_OUT1_INPUT].active)
			cvo1 = fmaxf(inputs[CV_OUT1_INPUT].value / 10.f, 0.f);

		if (inputs[CV_OUT2_INPUT].active)
			cvo2 = fmaxf(inputs[CV_OUT2_INPUT].value / 10.f, 0.f);
		
		if (inputs[CV_OUT3_INPUT].active)
			cvo3 = fmaxf(inputs[CV_OUT3_INPUT].value / 10.f, 0.f);
		
		if (inputs[CV_OUT4_INPUT].active)
			cvo4 = fmaxf(inputs[CV_OUT4_INPUT].value / 10.f, 0.f);

		// IF Mute Button is pushed
		if (params[MUTE1_BUTTON_PARAM].value == 1.0)
			cvo1 = 0.f;

		if (params[MUTE2_BUTTON_PARAM].value == 1.0)
			cvo2 = 0.f;
		
		if (params[MUTE3_BUTTON_PARAM].value == 1.0)
			cvo3 = 0.f;
		
		if (params[MUTE4_BUTTON_PARAM].value == 1.0)
			cvo4 = 0.f;

		// param Input channel 1 (knobs on top)
		float vol1 = params[INLEVEL1_ABCD_PARAM].value;
		float vol2 = params[INLEVEL2_ABCD_PARAM].value;
		float vol3 = params[INLEVEL3_ABCD_PARAM].value;
		float vol4 = params[INLEVEL4_ABCD_PARAM].value;

		// normalize inputs Channel 1
		float in1 = inputs[AUDIO_CH1_INPUT_A].normalize(0.0) * vol1;
		float in2 = inputs[AUDIO_CH1_INPUT_B].normalize(0.0) * vol1;
		float in3 = inputs[AUDIO_CH1_INPUT_C].normalize(0.0) * vol1;
		float in4 = inputs[AUDIO_CH1_INPUT_D].normalize(0.0) * vol1;
		// normalize inputs Channel 2
		float in5 = inputs[AUDIO_CH2_INPUT_A].normalize(0.0) * vol2;
		float in6 = inputs[AUDIO_CH2_INPUT_B].normalize(0.0) * vol2;
		float in7 = inputs[AUDIO_CH2_INPUT_C].normalize(0.0) * vol2;
		float in8 = inputs[AUDIO_CH2_INPUT_D].normalize(0.0) * vol2;
		// normalize inputs Channel 3
		float in9 = inputs[AUDIO_CH3_INPUT_A].normalize(0.0) * vol3;
		float in10 = inputs[AUDIO_CH3_INPUT_B].normalize(0.0) * vol3;
		float in11 = inputs[AUDIO_CH3_INPUT_C].normalize(0.0) * vol3;
		float in12 = inputs[AUDIO_CH3_INPUT_D].normalize(0.0) * vol3;
		// normalize inputs Channel 4
		float in13 = inputs[AUDIO_CH4_INPUT_A].normalize(0.0) * vol4;
		float in14 = inputs[AUDIO_CH4_INPUT_B].normalize(0.0) * vol4;
		float in15 = inputs[AUDIO_CH4_INPUT_C].normalize(0.0) * vol4;
		float in16 = inputs[AUDIO_CH4_INPUT_D].normalize(0.0) * vol4;


		// Set main 4 quadraphonic audio outputs
		outputs[AUDIO_OUTPUT].value = (in1 + in5 + in9 + in13) * params[OUTLEVEL1_PARAM].value * cvo1;
		outputs[AUDIO2_OUTPUT].value = (in2 + in6 + in10 + in14) * params[OUTLEVEL2_PARAM].value * cvo2;
		outputs[AUDIO3_OUTPUT].value = (in3 + in7 + in11 + in15) * params[OUTLEVEL3_PARAM].value * cvo3;
		outputs[AUDIO4_OUTPUT].value = (in4 + in8 + in12 + in16) * params[OUTLEVEL4_PARAM].value * cvo4;

		// set of extra outputs, combine Front and rear outputs to get L/R stereo channels
		outputs[AUDIO_AD_OUTPUT].value = (outputs[AUDIO_OUTPUT].value + outputs[AUDIO4_OUTPUT].value) * params[STOUTLEVEL_PARAM].value;
		outputs[AUDIO_BC_OUTPUT].value = (outputs[AUDIO2_OUTPUT].value + outputs[AUDIO3_OUTPUT].value) * params[STOUTLEVEL_PARAM].value;

		// Set of Mono mix outputs 1-2
		outputs[AUDIOL_OUTPUT].value = (outputs[AUDIO_OUTPUT].value + outputs[AUDIO2_OUTPUT].value + outputs[AUDIO3_OUTPUT].value + outputs[AUDIO4_OUTPUT].value) * params[OUTLEVEL_ST_PARAM].value;
		outputs[AUDIOR_OUTPUT].value = (outputs[AUDIO_OUTPUT].value + outputs[AUDIO2_OUTPUT].value + outputs[AUDIO3_OUTPUT].value + outputs[AUDIO4_OUTPUT].value) * params[OUTLEVEL_ST2_PARAM].value;


		// Vumeter
		//float signal_in = inputs[AUDIO_INPUT].value * params[INLEVEL_PARAM].value * cv;
		float signal_out1 = outputs[AUDIO_OUTPUT].value;
		float signal_out2 = outputs[AUDIO2_OUTPUT].value;
		float signal_out3 = outputs[AUDIO3_OUTPUT].value;
		float signal_out4 = outputs[AUDIO4_OUTPUT].value;

		float signal_out5 = outputs[AUDIO_AD_OUTPUT].value;
		float signal_out6 = outputs[AUDIO_BC_OUTPUT].value;

		vuBar.dBInterval = 10;

		// loop for each meter
		for (int i = 0; i < 5; i++){
			vuBar.setValue(signal_out1 / 10.0f);
			lights[METER_LIGHT_1 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out2 / 10.0f);
			lights[METER_LIGHT_2 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out3 / 10.0f);
			lights[METER_LIGHT_3 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out4 / 10.0f);
			lights[METER_LIGHT_4 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			// merged out vu meters
			vuBar.setValue(signal_out5 / 10.0f);
			lights[METER_LIGHT_AD + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out6 / 10.0f);
			lights[METER_LIGHT_BC + i].setBrightnessSmooth(vuBar.getBrightness(i));
		}
		
		// Autopot get data and show if cv is connected
		if (inputs[CV_OUT1_INPUT].active) {
			gain_affi2 =true; gain_gain2 = clamp(inputs[CV_OUT1_INPUT].value,-0.001,10.001) ;} 
		else {gain_affi2 =false; gain_gain2 = params[OUTLEVEL1_PARAM].value ;}


		if (inputs[CV_OUT2_INPUT].active) {
			gain_affi3 =true; gain_gain3 = clamp(inputs[CV_OUT2_INPUT].value,-0.001,10.001) ;} 
		else {gain_affi3 =false; gain_gain3 = params[OUTLEVEL2_PARAM].value ;}

		if (inputs[CV_OUT3_INPUT].active) {
			gain_affi4 =true; gain_gain4 = clamp(inputs[CV_OUT3_INPUT].value,-0.001,10.001) ;} 
		else {gain_affi4 =false; gain_gain4 = params[OUTLEVEL3_PARAM].value ;}

		if (inputs[CV_OUT4_INPUT].active) {
			gain_affi5 =true; gain_gain5 = clamp(inputs[CV_OUT4_INPUT].value,-0.001,10.001) ;} 
		else {gain_affi5 =false; gain_gain5 = params[OUTLEVEL4_PARAM].value ;}

	}
	VUMeter vuBar;
};

// UI Panel
struct QS_MergerWidget : ModuleWidget {
	
	QS_MergerWidget(QS_Merger *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/bg_merger.svg")));

		// Inputs Knobs
		addParam(ParamWidget::create<QS_potsmall>(Vec(20, 24), module, QS_Merger::INLEVEL1_ABCD_PARAM, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<QS_potsmall>(Vec(65, 24), module, QS_Merger::INLEVEL2_ABCD_PARAM, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<QS_potsmall>(Vec(110, 24), module, QS_Merger::INLEVEL3_ABCD_PARAM, 0.0, 1.0, 1.0));
		addParam(ParamWidget::create<QS_potsmall>(Vec(155, 24), module, QS_Merger::INLEVEL4_ABCD_PARAM, 0.0, 1.0, 1.0));


		// All inputs jacks	
		// Channel 1
		addInput(Port::create<QS_jackgoldPort>(Vec(20, 100), Port::INPUT, module, QS_Merger::AUDIO_CH1_INPUT_A));
		addInput(Port::create<QS_jackgoldPort>(Vec(20, 151), Port::INPUT, module, QS_Merger::AUDIO_CH1_INPUT_B));
		addInput(Port::create<QS_jackgoldPort>(Vec(20, 202), Port::INPUT, module, QS_Merger::AUDIO_CH1_INPUT_C));
		addInput(Port::create<QS_jackgoldPort>(Vec(20, 254), Port::INPUT, module, QS_Merger::AUDIO_CH1_INPUT_D));

		// Channel 2
		addInput(Port::create<QS_jackgoldPort>(Vec(65, 100), Port::INPUT, module, QS_Merger::AUDIO_CH2_INPUT_A));
		addInput(Port::create<QS_jackgoldPort>(Vec(65, 151), Port::INPUT, module, QS_Merger::AUDIO_CH2_INPUT_B));
		addInput(Port::create<QS_jackgoldPort>(Vec(65, 202), Port::INPUT, module, QS_Merger::AUDIO_CH2_INPUT_C));
		addInput(Port::create<QS_jackgoldPort>(Vec(65, 254), Port::INPUT, module, QS_Merger::AUDIO_CH2_INPUT_D));

		// Channel 3
		addInput(Port::create<QS_jackgoldPort>(Vec(110, 100), Port::INPUT, module, QS_Merger::AUDIO_CH3_INPUT_A));
		addInput(Port::create<QS_jackgoldPort>(Vec(110, 151), Port::INPUT, module, QS_Merger::AUDIO_CH3_INPUT_B));
		addInput(Port::create<QS_jackgoldPort>(Vec(110, 202), Port::INPUT, module, QS_Merger::AUDIO_CH3_INPUT_C));
		addInput(Port::create<QS_jackgoldPort>(Vec(110, 254), Port::INPUT, module, QS_Merger::AUDIO_CH3_INPUT_D));

		// Channel 4
		addInput(Port::create<QS_jackgoldPort>(Vec(155, 100), Port::INPUT, module, QS_Merger::AUDIO_CH4_INPUT_A));
		addInput(Port::create<QS_jackgoldPort>(Vec(155, 151), Port::INPUT, module, QS_Merger::AUDIO_CH4_INPUT_B));
		addInput(Port::create<QS_jackgoldPort>(Vec(155, 202), Port::INPUT, module, QS_Merger::AUDIO_CH4_INPUT_C));
		addInput(Port::create<QS_jackgoldPort>(Vec(155, 254), Port::INPUT, module, QS_Merger::AUDIO_CH4_INPUT_D));
		
	// Outputs section
		// outputs
		addOutput(Port::create<QS_jackredPort>(Vec(214, 98), Port::OUTPUT, module, QS_Merger::AUDIO_OUTPUT));
		addOutput(Port::create<QS_jackredPort>(Vec(214, 150), Port::OUTPUT, module, QS_Merger::AUDIO2_OUTPUT));
		addOutput(Port::create<QS_jackredPort>(Vec(214, 202), Port::OUTPUT, module, QS_Merger::AUDIO3_OUTPUT));
		addOutput(Port::create<QS_jackredPort>(Vec(214, 254), Port::OUTPUT, module, QS_Merger::AUDIO4_OUTPUT));

		// params for output levels
		addParam(ParamWidget::create<QS_potsmall>(Vec(259, 98), module, QS_Merger::OUTLEVEL1_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay2 = new QS_AutomatedPot();
			gaindisplay2->box.pos = Vec(274.75, 113.75); // by the center + 15.75!
			gaindisplay2->d = 8.3; // was 9
			gaindisplay2->gainX = &module->gain_gain2;
			gaindisplay2->affich = &module->gain_affi2;
			addChild(gaindisplay2);
		}
		
		addParam(ParamWidget::create<QS_potsmall>(Vec(259, 151), module, QS_Merger::OUTLEVEL2_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay3 = new QS_AutomatedPot();
			gaindisplay3->box.pos = Vec(274.75, 166.75); // by the center + 15.75!
			gaindisplay3->d = 8.3; // was 9
			gaindisplay3->gainX = &module->gain_gain3;
			gaindisplay3->affich = &module->gain_affi3;
			addChild(gaindisplay3);
		}
		
		addParam(ParamWidget::create<QS_potsmall>(Vec(259, 202), module, QS_Merger::OUTLEVEL3_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay4 = new QS_AutomatedPot();
			gaindisplay4->box.pos = Vec(274.75, 217.75); // by the center + 15.75!
			gaindisplay4->d = 8.3; // was 9
			gaindisplay4->gainX = &module->gain_gain4;
			gaindisplay4->affich = &module->gain_affi4;
			addChild(gaindisplay4);
		}
		
		addParam(ParamWidget::create<QS_potsmall>(Vec(259, 254), module, QS_Merger::OUTLEVEL4_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay5 = new QS_AutomatedPot();
			gaindisplay5->box.pos = Vec(274.75, 269.75); // by the center + 15.75!
			gaindisplay5->d = 8.3; // was 9
			gaindisplay5->gainX = &module->gain_gain5;
			gaindisplay5->affich = &module->gain_affi5;
			addChild(gaindisplay5);
		}


		// CV inputs
		addInput(Port::create<QS_cvsilverPort>(Vec(304, 102), Port::INPUT, module, QS_Merger::CV_OUT1_INPUT));
		addInput(Port::create<QS_cvsilverPort>(Vec(304, 155), Port::INPUT, module, QS_Merger::CV_OUT2_INPUT));
		addInput(Port::create<QS_cvsilverPort>(Vec(304, 206), Port::INPUT, module, QS_Merger::CV_OUT3_INPUT));
		addInput(Port::create<QS_cvsilverPort>(Vec(304, 258), Port::INPUT, module, QS_Merger::CV_OUT4_INPUT));

		// Mute buttons
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(338, 100), module, QS_Merger::MUTE1_BUTTON_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(338, 152), module, QS_Merger::MUTE2_BUTTON_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(338, 204), module, QS_Merger::MUTE3_BUTTON_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(338, 256), module, QS_Merger::MUTE4_BUTTON_PARAM, 0.0, 1.0, 0.0));

		// merged top outputs
		addOutput(Port::create<QS_jackredPort>(Vec(214, 25), Port::OUTPUT, module, QS_Merger::AUDIO_AD_OUTPUT));
		addOutput(Port::create<QS_jackredPort>(Vec(259, 25), Port::OUTPUT, module, QS_Merger::AUDIO_BC_OUTPUT));
		addParam(ParamWidget::create<QS_potsmall>(Vec(301, 23), module, QS_Merger::STOUTLEVEL_PARAM, 0.0, 1.0, 0.0));


		// Bottom mono mixed outputs 1
		
		addOutput(Port::create<QS_jackblackPort>(Vec(20, 311), Port::OUTPUT, module, QS_Merger::AUDIOL_OUTPUT));
		addParam(ParamWidget::create<QS_potsmall>(Vec(63, 310), module, QS_Merger::OUTLEVEL_ST_PARAM, 0.0, 1.0, 0.0));

		addOutput(Port::create<QS_jackblackPort>(Vec(110, 310), Port::OUTPUT, module, QS_Merger::AUDIOR_OUTPUT));
		addParam(ParamWidget::create<QS_potsmall>(Vec(154, 310), module, QS_Merger::OUTLEVEL_ST2_PARAM, 0.0, 1.0, 0.0));

		// Vu meters
		static const float ledCol = 375;
        static const float offsetY = 8;
        static const float startY = 98;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY + offsetY * 0), module, QS_Merger::METER_LIGHT_1 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY + offsetY * 1), module, QS_Merger::METER_LIGHT_1 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 2), module, QS_Merger::METER_LIGHT_1 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 3), module, QS_Merger::METER_LIGHT_1 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 4), module, QS_Merger::METER_LIGHT_1 + 4));

        static const float startY2 = 151;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY2 + offsetY * 0), module, QS_Merger::METER_LIGHT_2 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY2 + offsetY * 1), module, QS_Merger::METER_LIGHT_2 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY2 + offsetY * 2), module, QS_Merger::METER_LIGHT_2 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY2 + offsetY * 3), module, QS_Merger::METER_LIGHT_2 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY2 + offsetY * 4), module, QS_Merger::METER_LIGHT_2 + 4));

        static const float startY3 = 202;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY3 + offsetY * 0), module, QS_Merger::METER_LIGHT_3 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY3 + offsetY * 1), module, QS_Merger::METER_LIGHT_3 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY3 + offsetY * 2), module, QS_Merger::METER_LIGHT_3 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY3 + offsetY * 3), module, QS_Merger::METER_LIGHT_3 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY3 + offsetY * 4), module, QS_Merger::METER_LIGHT_3 + 4));

        static const float startY4 = 254;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY4 + offsetY * 0), module, QS_Merger::METER_LIGHT_4 + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY4 + offsetY * 1), module, QS_Merger::METER_LIGHT_4 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY4 + offsetY * 2), module, QS_Merger::METER_LIGHT_4 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY4 + offsetY * 3), module, QS_Merger::METER_LIGHT_4 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY4 + offsetY * 4), module, QS_Merger::METER_LIGHT_4 + 4));


		static const float startYbc = 25;
        addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startYbc + offsetY * 0), module, QS_Merger::METER_LIGHT_BC + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startYbc + offsetY * 1), module, QS_Merger::METER_LIGHT_BC + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startYbc + offsetY * 2), module, QS_Merger::METER_LIGHT_BC + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startYbc + offsetY * 3), module, QS_Merger::METER_LIGHT_BC + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startYbc + offsetY * 4), module, QS_Merger::METER_LIGHT_BC + 4));

		static const float ledCol2 = 359;
		addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol2, startYbc + offsetY * 0), module, QS_Merger::METER_LIGHT_AD + 0));
        addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol2, startYbc + offsetY * 1), module, QS_Merger::METER_LIGHT_AD + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol2, startYbc + offsetY * 2), module, QS_Merger::METER_LIGHT_AD + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol2, startYbc + offsetY * 3), module, QS_Merger::METER_LIGHT_AD + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol2, startYbc + offsetY * 4), module, QS_Merger::METER_LIGHT_AD + 4));


	}

};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelQS_Merger = Model::create<QS_Merger, QS_MergerWidget>("Quadraphonics", "QS_Merger", ":: Quad Matrix Mixer QM-1200 MKI", MIXER_TAG, UTILITY_TAG);
