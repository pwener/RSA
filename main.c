#include "console.h"

int main()
{
	Options options;
	options = get_standard_options_values();

	while(options.main == CONTINUE)
	{
		options = run_functions(options);
	}
	return 0;
}