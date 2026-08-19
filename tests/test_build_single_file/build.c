#include "../../builder.h"

void BuildScript( BuilderOptions *options ) {
	BuildConfig *config = CreateBuildConfig( options, "single_file", BINARY_TYPE_EXE );
	SetBinaryName( config, "test_build_single_file" );
	AddSourceFiles( config, "main.c" );
}
