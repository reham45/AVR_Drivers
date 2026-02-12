#ifndef _BIT_MATH_H_
#define  _BIT_MATH_H_

#define SET_BIT(Reg,bitno) (Reg|=(1<<bitno))
#define CLR_BIT(Reg,bitno) (Reg&=(~(1<<bitno)))
#define TOGGLE_BIT(Reg,bitno) (Reg^=(1<<bitno))
#define GET_BIT(Reg,bitno) ((Reg>>bitno)&1)

#endif
