typedef enum {
	EOT= 4,				// END OF TRANSMISSION (CTRL + D)
	BS = 8,				// BACSPACE
	LF = 10,			// ENTER
	ENTER = 10,			// ENTER
	SO = 14,			// SHIFT OUT
	SI = 15,			// SHIFT IN
	ESC = 27,			// ESCAPE
	BEGIN_NORMAL = 32,	// BEGINING OF NORMAL ASCII CHARS
	STAR_KEY = 42,		// *
	NUM_3 = 51,			// 3
	C_KEY = 67,			// C
	D_KEY = 68,			// D
	F_KEY = 70,			// F
	H_KEY = 72,			// H
	O_KEY = 79,			// O
	OPEN_S_B = 91,		// OPEN SQUARE BRAQUET
	END_NORMAL = 126,	// ENDING OF NORMAL ASCII CHARS
	TILDE = 126,		// ~
	DEL = 127,			// DELETE LEFT
} ASCII;

typedef enum {
	DEL_L = -100,
	DEL_R = -101,		// DELETE RIGHT
	END = -102,			// END KEY
	BEGIN = -103,		// BEGIN KEY
	RIGHT_A_K = -104,	// RIGHT ARROW KEY
	LEFT_A_K = -105,	// LEFT ARROW KEY
	ENTER_CMD = -2,	// ENTER
	EOT_CMD = -3,		// END OF TRANSMISSION (CTRL + D)
	NO_CMD = -1,		// NO CMD
	WAIT_CMD = 0,		// WAIT FOR OTHER CHAR
} CMD;

