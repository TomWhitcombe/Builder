#include "../../builder.h"

void BuildScript( BuilderOptions *options ) {
	BuildConfig *config = CreateBuildConfig( options, "multiple_files", BINARY_TYPE_EXE );
	SetBinaryName( config, "test_multiple_files" );
	AddSourceFiles( config, "src/main.c", "src/test1.c", "src/test2.c" );
	AddDefines( config, "MYCONFIG_DOES_A_THING" );

	if ( HasCommandLineArg( options, "--release" ) ) {
		AddDefines( config, "NDEBUG" );
	} else {
		AddDefines( config, "_DEBUG" );
	}
}
