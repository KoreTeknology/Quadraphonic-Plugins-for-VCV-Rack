//***********************************************************************************************
//
// QuadraphonicStudio Modules for VCV Rack by Uriel deveaud 
// Module name: Single Track Diffuser
// https://github.com/KoreTeknology/Quadraphonic-Plugins-for-VCV-Rack
//  
//***********************************************************************************************

#include "Quadraphonics.hpp"
#include "dsp/digital.hpp"
#include "dsp/vumeter.hpp"

// Main definitions
struct QS_Diffuser : Module {
	enum ParamIds {
		INLEVEL_PARAM,
		OUTLEVEL1_PARAM,
		OUTLEVEL2_PARAM,
		OUTLEVEL3_PARAM,
		OUTLEVEL4_PARAM,
		DOUTLEVEL_PARAM,
		MUTE1_BTN_PARAM,
		MUTE2_BTN_PARAM,
		MUTE3_BTN_PARAM,
		MUTE4_BTN_PARAM,
		MUTE5_BTN_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CV1_INPUT,
		CV_OUT1_INPUT,
		CV_OUT2_INPUT,
		CV_OUT3_INPUT,
		CV_OUT4_INPUT,
		AUDIO_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		A1_OUTPUT,
		A2_OUTPUT,
		A3_OUTPUT,
		A4_OUTPUT,
		ADIRECT_OUTPUT,
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

	float x = 0;
	float y = 0;
	int length = 0;

	float gain_gain ;
	int gain_affi ;
	float gain_gain2 ;
	int gain_affi2 ;
	float gain_gain3 ;
	int gain_affi3 ;
	float gain_gain4 ;
	int gain_affi4 ;
	float gain_gain5 ;
	int gain_affi5 ;

	QS_Diffuser() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	
	// Interative Features
	void step() override {
		float cv = 1.f;
		float cvo1 = 1.f;
		float cvo2 = 1.f;
		float cvo3 = 1.f;
		float cvo4 = 1.f;

		// IF a jack is connected to CV input
		if (inputs[CV1_INPUT].active)
			cv = fmaxf(inputs[CV1_INPUT].value / 10.f, 0.f);

		if (inputs[CV_OUT1_INPUT].active)
			cvo1 = fmaxf(inputs[CV_OUT1_INPUT].value / 10.f, 0.f);

		if (inputs[CV_OUT2_INPUT].active)
			cvo2 = fmaxf(inputs[CV_OUT2_INPUT].value / 10.f, 0.f);
		
		if (inputs[CV_OUT3_INPUT].active)
			cvo3 = fmaxf(inputs[CV_OUT3_INPUT].value / 10.f, 0.f);
		
		if (inputs[CV_OUT4_INPUT].active)
			cvo4 = fmaxf(inputs[CV_OUT4_INPUT].value / 10.f, 0.f);

		// IF Mute Button is pushed
		if (params[MUTE1_BTN_PARAM].value == 1.0)
			cv = 0.f;

		if (params[MUTE2_BTN_PARAM].value == 1.0)
			cvo1 = 0.f;

		if (params[MUTE3_BTN_PARAM].value == 1.0)
			cvo2 = 0.f;
		
		if (params[MUTE4_BTN_PARAM].value == 1.0)
			cvo3 = 0.f;
		
		if (params[MUTE5_BTN_PARAM].value == 1.0)
			cvo4 = 0.f;

		// Normalize at start audio input
		float in1 = inputs[AUDIO_INPUT].normalize(0.0);

		// calculate final output levels
		outputs[A1_OUTPUT].value = in1 * params[INLEVEL_PARAM].value * cv * params[OUTLEVEL1_PARAM].value * cvo1;
		outputs[A2_OUTPUT].value = in1 * params[INLEVEL_PARAM].value * cv * params[OUTLEVEL2_PARAM].value * cvo2;
		outputs[A3_OUTPUT].value = in1 * params[INLEVEL_PARAM].value * cv * params[OUTLEVEL3_PARAM].value * cvo3;
		outputs[A4_OUTPUT].value = in1 * params[INLEVEL_PARAM].value * cv * params[OUTLEVEL4_PARAM].value * cvo4;
		outputs[ADIRECT_OUTPUT].value = in1 * params[DOUTLEVEL_PARAM].value;


		// Vumeter
		float signal_in = inputs[AUDIO_INPUT].value * params[INLEVEL_PARAM].value * cv;
		float signal_out1 = outputs[A1_OUTPUT].value;
		float signal_out2 = outputs[A2_OUTPUT].value;
		float signal_out3 = outputs[A3_OUTPUT].value;
		float signal_out4 = outputs[A4_OUTPUT].value;

		vuBar.dBInterval = 10;
		// loop for each meter
		for (int i = 0; i < 5; i++){
			vuBar.setValue(signal_in / 10.0f);
			lights[METER_LIGHT_0 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out1 / 10.0f);
			lights[METER_LIGHT_1 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out2 / 10.0f);
			lights[METER_LIGHT_2 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out3 / 10.0f);
			lights[METER_LIGHT_3 + i].setBrightnessSmooth(vuBar.getBrightness(i));
			vuBar.setValue(signal_out4 / 10.0f);
			lights[METER_LIGHT_4 + i].setBrightnessSmooth(vuBar.getBrightness(i));
		}

		// Autopot get data and show if cv is connected
		if (inputs[CV1_INPUT].active) {
			gain_affi =true; gain_gain = clamp(inputs[CV1_INPUT].value,-0.001,10.001) ;} 
		else {gain_affi =false; gain_gain = params[INLEVEL_PARAM].value ;}

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
struct QS_DiffuserWidget : ModuleWidget {
	QS_DiffuserWidget(QS_Diffuser *module) : ModuleWidget(module) {
		setPanel(SVG::load(assetPlugin(plugin, "res/bg_diffuser.svg")));
		/*
		addChild(Widget::create<QS_Screw>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<QS_Screw>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<QS_Screw>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(Widget::create<QS_Screw>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		*/
		// Input section
		addInput(Port::create<QS_jackgoldPort>(Vec(20, 25), Port::INPUT, module, QS_Diffuser::AUDIO_INPUT));

		// Autopot Input
		addParam(ParamWidget::create<QS_potsmall>(Vec(64, 24), module, QS_Diffuser::INLEVEL_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay = new QS_AutomatedPot();
			gaindisplay->box.pos = Vec(79.75, 39.75); // by the center + 15.75!
			gaindisplay->d = 8.3; // was 9
			gaindisplay->gainX = &module->gain_gain;
			gaindisplay->affich = &module->gain_affi;
			addChild(gaindisplay);
		}

		addInput(Port::create<QS_cvsilverPort>(Vec(108, 28), Port::INPUT, module, QS_Diffuser::CV1_INPUT));
		
		// Outputs section
		addOutput(Port::create<QS_jacksilverPort>(Vec(20, 100), Port::OUTPUT, module, QS_Diffuser::A1_OUTPUT));
		addOutput(Port::create<QS_jackredPort>(Vec(20, 151), Port::OUTPUT, module, QS_Diffuser::A2_OUTPUT));
		addOutput(Port::create<QS_jacksilverPort>(Vec(20, 204), Port::OUTPUT, module, QS_Diffuser::A3_OUTPUT));
		addOutput(Port::create<QS_jackredPort>(Vec(20, 256), Port::OUTPUT, module, QS_Diffuser::A4_OUTPUT));
		
		// Outputs Knob with autopot
		addParam(ParamWidget::create<QS_potsmall>(Vec(64, 98), module, QS_Diffuser::OUTLEVEL1_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay2 = new QS_AutomatedPot();
			gaindisplay2->box.pos = Vec(79.75, 113.75); // by the center + 15.75!
			gaindisplay2->d = 8.3; // was 9
			gaindisplay2->gainX = &module->gain_gain2;
			gaindisplay2->affich = &module->gain_affi2;
			addChild(gaindisplay2);
		}

		addParam(ParamWidget::create<QS_potsmall>(Vec(64, 151), module, QS_Diffuser::OUTLEVEL2_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay3 = new QS_AutomatedPot();
			gaindisplay3->box.pos = Vec(79.75, 166.75); // by the center + 15.75!
			gaindisplay3->d = 8.3; // was 9
			gaindisplay3->gainX = &module->gain_gain3;
			gaindisplay3->affich = &module->gain_affi3;
			addChild(gaindisplay3);
		}

		addParam(ParamWidget::create<QS_potsmall>(Vec(64, 202), module, QS_Diffuser::OUTLEVEL3_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay4 = new QS_AutomatedPot();
			gaindisplay4->box.pos = Vec(79.75, 217.75); // by the center + 15.75!
			gaindisplay4->d = 8.3; // was 9
			gaindisplay4->gainX = &module->gain_gain4;
			gaindisplay4->affich = &module->gain_affi4;
			addChild(gaindisplay4);
		}

		addParam(ParamWidget::create<QS_potsmall>(Vec(64, 254), module, QS_Diffuser::OUTLEVEL4_PARAM, 0.0, 1.0, 0.0));
		{
			QS_AutomatedPot *gaindisplay5 = new QS_AutomatedPot();
			gaindisplay5->box.pos = Vec(79.75, 269.75); // by the center + 15.75!
			gaindisplay5->d = 8.3; // was 9
			gaindisplay5->gainX = &module->gain_gain5;
			gaindisplay5->affich = &module->gain_affi5;
			addChild(gaindisplay5);
		}

		// CV input jack
		addInput(Port::create<QS_cvsilverPort>(Vec(108, 102), Port::INPUT, module, QS_Diffuser::CV_OUT1_INPUT));
		addInput(Port::create<QS_cvsilverPort>(Vec(108, 155), Port::INPUT, module, QS_Diffuser::CV_OUT2_INPUT));
		addInput(Port::create<QS_cvsilverPort>(Vec(108, 206), Port::INPUT, module, QS_Diffuser::CV_OUT3_INPUT));
		addInput(Port::create<QS_cvsilverPort>(Vec(108, 258), Port::INPUT, module, QS_Diffuser::CV_OUT4_INPUT));

		// Direct output > Chain
		addOutput(Port::create<QS_jackblackPort>(Vec(20, 311), Port::OUTPUT, module, QS_Diffuser::ADIRECT_OUTPUT));
		addParam(ParamWidget::create<QS_potsmall>(Vec(64, 309), module, QS_Diffuser::DOUTLEVEL_PARAM, 0.0, 1.0, 0.0));

		// Mute buttons
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(142, 25), module, QS_Diffuser::MUTE1_BTN_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(142, 100), module, QS_Diffuser::MUTE2_BTN_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(142, 151), module, QS_Diffuser::MUTE3_BTN_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(142, 202), module, QS_Diffuser::MUTE4_BTN_PARAM, 0.0, 1.0, 0.0));
		addParam(ParamWidget::create<BtnMuteSwitch>(Vec(142, 254), module, QS_Diffuser::MUTE5_BTN_PARAM, 0.0, 1.0, 0.0));

		static const float ledCol = 180;
        static const float offsetY = 8;
        static const float startY = 98;
            addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol, startY + offsetY * 0), module, QS_Diffuser::METER_LIGHT_1 + 0));
            addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol, startY + offsetY * 1), module, QS_Diffuser::METER_LIGHT_1 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 2), module, QS_Diffuser::METER_LIGHT_1 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 3), module, QS_Diffuser::METER_LIGHT_1 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol, startY + offsetY * 4), module, QS_Diffuser::METER_LIGHT_1 + 4));

		static const float ledCol2 = 180;
        //static const float offsetY = 8;
        static const float startY2 = 151;
            addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol2, startY2 + offsetY * 0), module, QS_Diffuser::METER_LIGHT_2 + 0));
            addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol2, startY2 + offsetY * 1), module, QS_Diffuser::METER_LIGHT_2 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol2, startY2 + offsetY * 2), module, QS_Diffuser::METER_LIGHT_2 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol2, startY2 + offsetY * 3), module, QS_Diffuser::METER_LIGHT_2 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol2, startY2 + offsetY * 4), module, QS_Diffuser::METER_LIGHT_2 + 4));

		static const float ledCol3 = 180;
        //static const float offsetY = 8;
        static const float startY3 = 202;
            addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol3, startY3 + offsetY * 0), module, QS_Diffuser::METER_LIGHT_3 + 0));
            addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol3, startY3 + offsetY * 1), module, QS_Diffuser::METER_LIGHT_3 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol3, startY3 + offsetY * 2), module, QS_Diffuser::METER_LIGHT_3 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol3, startY3 + offsetY * 3), module, QS_Diffuser::METER_LIGHT_3 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol3, startY3 + offsetY * 4), module, QS_Diffuser::METER_LIGHT_3 + 4));

		static const float ledCol4 = 180;
        //static const float offsetY = 8;
        static const float startY4 = 254;
            addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol4, startY4 + offsetY * 0), module, QS_Diffuser::METER_LIGHT_4 + 0));
            addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol4, startY4 + offsetY * 1), module, QS_Diffuser::METER_LIGHT_4 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol4, startY4 + offsetY * 2), module, QS_Diffuser::METER_LIGHT_4 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol4, startY4 + offsetY * 3), module, QS_Diffuser::METER_LIGHT_4 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol4, startY4 + offsetY * 4), module, QS_Diffuser::METER_LIGHT_4 + 4));
        
		static const float ledCol5 = 180;
        //static const float offsetY = 8;
        static const float startY5 = 24;
            addChild(ModuleLightWidget::create<VuMeter<RedLight>>(Vec(ledCol5, startY5 + offsetY * 0), module, QS_Diffuser::METER_LIGHT_0 + 0));
            addChild(ModuleLightWidget::create<VuMeter<GreenLight>>(Vec(ledCol5, startY5 + offsetY * 1), module, QS_Diffuser::METER_LIGHT_0 + 1));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol5, startY5 + offsetY * 2), module, QS_Diffuser::METER_LIGHT_0 + 2));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol5, startY5 + offsetY * 3), module, QS_Diffuser::METER_LIGHT_0 + 3));
        addChild(ModuleLightWidget::create<VuMeter<OrangeLight>>(Vec(ledCol5, startY5 + offsetY * 4), module, QS_Diffuser::METER_LIGHT_0 + 4));
        
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelQS_Diffuser = Model::create<QS_Diffuser, QS_DiffuserWidget>("Quadraphonics", "QS_Diffuser", ":: Mono Track Diffuser v1.2", MIXER_TAG, UTILITY_TAG);
