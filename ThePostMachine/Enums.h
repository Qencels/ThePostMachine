#pragma once

namespace postMachine {

	enum Commands {
		about,
		menu,
		set_alg,
		set_marks,
		set_carriage,
		show_points,
		show_alg,
		clear,
		start,
		exitC,
		importF,
		exportF,
	};

	enum ErrorCodes {
		WRONG_PATH_OR_NO_PERMISSION,
		WRONG_COMMAND,
		WRONG_ARG
	};

}

