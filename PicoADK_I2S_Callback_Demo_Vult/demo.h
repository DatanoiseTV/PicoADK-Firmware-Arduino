
/* Code automatically generated by Vult https://github.com/modlfo/vult */
#ifndef DEMO_H
#define DEMO_H
#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "demo.tables.h"

typedef struct Demo__ctx_type_0 {
   fix16_t x;
} Demo__ctx_type_0;

typedef Demo__ctx_type_0 Demo_smooth_type;

static_inline void Demo__ctx_type_0_init(Demo__ctx_type_0 &_output_){
   Demo__ctx_type_0 _ctx;
   _ctx.x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void Demo_smooth_init(Demo__ctx_type_0 &_output_){
   Demo__ctx_type_0_init(_output_);
   return ;
}

static_inline fix16_t Demo_smooth(Demo__ctx_type_0 &_ctx, fix16_t input){
   _ctx.x = (_ctx.x + fix_mul(0x147 /* 0.005000 */,(input + (- _ctx.x))));
   return _ctx.x;
}

typedef struct Demo__ctx_type_1 {
   fix16_t pre_x;
} Demo__ctx_type_1;

typedef Demo__ctx_type_1 Demo_change_type;

static_inline void Demo__ctx_type_1_init(Demo__ctx_type_1 &_output_){
   Demo__ctx_type_1 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

static_inline void Demo_change_init(Demo__ctx_type_1 &_output_){
   Demo__ctx_type_1_init(_output_);
   return ;
}

static_inline uint8_t Demo_change(Demo__ctx_type_1 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

static_inline fix16_t Demo_pitchToRate(fix16_t d){
   return fix_mul(0xc /* 0.000185 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,d)));
};

typedef struct Demo__ctx_type_3 {
   fix16_t rate;
   fix16_t phase;
   Demo__ctx_type_1 _inst1f1;
} Demo__ctx_type_3;

typedef Demo__ctx_type_3 Demo_phasor_type;

void Demo__ctx_type_3_init(Demo__ctx_type_3 &_output_);

static_inline void Demo_phasor_init(Demo__ctx_type_3 &_output_){
   Demo__ctx_type_3_init(_output_);
   return ;
}

fix16_t Demo_phasor(Demo__ctx_type_3 &_ctx, fix16_t pitch, uint8_t reset);

typedef struct Demo__ctx_type_4 {
   fix16_t volume;
   fix16_t pre_phase1;
   fix16_t pitch;
   fix16_t detune;
   Demo__ctx_type_0 _inst4c7;
   Demo__ctx_type_3 _inst327;
   Demo__ctx_type_0 _inst2c7;
   Demo__ctx_type_3 _inst127;
} Demo__ctx_type_4;

typedef Demo__ctx_type_4 Demo_process_type;

void Demo__ctx_type_4_init(Demo__ctx_type_4 &_output_);

static_inline void Demo_process_init(Demo__ctx_type_4 &_output_){
   Demo__ctx_type_4_init(_output_);
   return ;
}

fix16_t Demo_process(Demo__ctx_type_4 &_ctx, fix16_t input);

typedef Demo__ctx_type_4 Demo_noteOn_type;

static_inline void Demo_noteOn_init(Demo__ctx_type_4 &_output_){
   Demo__ctx_type_4_init(_output_);
   return ;
}

static_inline void Demo_noteOn(Demo__ctx_type_4 &_ctx, int note, int velocity, int channel){
   _ctx.pitch = int_to_fix(note);
};

typedef Demo__ctx_type_4 Demo_noteOff_type;

static_inline void Demo_noteOff_init(Demo__ctx_type_4 &_output_){
   Demo__ctx_type_4_init(_output_);
   return ;
}

static_inline void Demo_noteOff(Demo__ctx_type_4 &_ctx, int note, int channel){
}

typedef Demo__ctx_type_4 Demo_controlChange_type;

static_inline void Demo_controlChange_init(Demo__ctx_type_4 &_output_){
   Demo__ctx_type_4_init(_output_);
   return ;
}

static_inline void Demo_controlChange(Demo__ctx_type_4 &_ctx, int control, int value, int channel){
   if(control == 30){
      _ctx.volume = fix_mul(0x204 /* 0.007874 */,int_to_fix(value));
   }
   if(control == 31){
      _ctx.detune = fix_mul(0x204 /* 0.007874 */,int_to_fix(value));
   }
}

typedef Demo__ctx_type_4 Demo_default_type;

static_inline void Demo_default_init(Demo__ctx_type_4 &_output_){
   Demo__ctx_type_4_init(_output_);
   return ;
}

static_inline void Demo_default(Demo__ctx_type_4 &_ctx){
   _ctx.volume = 0x10000 /* 1.000000 */;
   _ctx.pitch = 0x2d0000 /* 45.000000 */;
   _ctx.detune = 0x0 /* 0.000000 */;
}



#endif // DEMO_H