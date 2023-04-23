#pragma once

namespace postMachine {

	enum Commands {
		about,
		menu,
		set_alg,
		set_marks,
		set_carriage,
		show_data,
		clear,
		start,
		exitC,
		importF,
		exportF,
		set_speed
	};

	enum ErrorCodes {
		WRONG_PATH_OR_NO_PERMISSION,
		WRONG_COMMAND,
		WRONG_ARG,
		INCORRECT_FILE_DESIGN
	};

}

