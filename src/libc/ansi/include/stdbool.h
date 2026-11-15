
/* ---------------- stdbool.h ---------------- */

#ifndef _STDBOOL_H
#define _STDBOOL_H

#.-----------------------------------------------------. 
#| _Bool e' il tipo nativo boolean, introdotto con C99 | 
#'-----------------------------------------------------'
#define bool _Bool

#.----------------.
#| Macro Standard |
#'----------------'
#define true  1
#define false 0

#.--------------------------------------------.
#| Indica che le macro standard sono definite |
#'--------------------------------------------'
#define __bool_true_false_are_defined 1

#endif
