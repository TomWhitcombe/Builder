#include "../../builder.h"

void BuildScript( BuilderOptions *options ) {
	BuildConfig *libConfig = CreateBuildConfig( options, "lib", BINARY_TYPE_DYNAMIC_LIBRARY );
	SetBinaryName( libConfig, "test_dynamic_lib" );
	AddSourceFiles( libConfig, "lib/mathlib.c" );
	AddDefines( libConfig, "MATHLIB_BUILDING" );

	BuildConfig *programConfig = CreateBuildConfig( options, "program", BINARY_TYPE_EXE );
	SetBinaryName( programConfig, "test_dynamic_lib_program" );
	AddDependencies( programConfig, libConfig );
	AddSourceFiles( programConfig, "program/main.c" );
	AddIncludes( programConfig, "lib" );
#if defined( _WIN32 )
	AddLibs( programConfig, "test_dynamic_lib.lib" );
#else
	AddLibs( programConfig, "./test_dynamic_lib.so" );
	AddLinkerArguments( programConfig, "-Wl,-rpath,$ORIGIN" );
#endif

	options->defaultConfig = programConfig;
}
