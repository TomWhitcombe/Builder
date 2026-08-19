#include "../../builder.h"
#include "../../builder_vs_code.h"

void BuildScript( BuilderOptions *options ) {
	BuildConfig *config = CreateBuildConfig( options, "config", BINARY_TYPE_EXE );
	SetBinaryName( config, "test_generate_vs_code_json" );
	AddSourceFiles( config, "main.c" );

	if ( HasCommandLineArg( options, "--release" ) ) {
		SetBinaryFolder( config, "bin/release" );
	} else {
		SetBinaryFolder( config, "bin/debug" );
	}

	options->defaultConfig = config;

	if ( HasCommandLineArg( options, "--vscode" ) ) {
		VSCodeCppPropertiesConfig cppPropertiesConfigs[] = {
			{ .config = config, .intelliSenseMode = VSCODE_INTELLISENSE_MODE_LINUX_CLANG_X64 },
		};

		VSCodeTaskConfig taskConfigs[] = {
			{ .config = config },
			{ .config = config, .additionalBuildArgs = (const char *[]) { "--release", NULL } },
		};

		VSCodeLaunchConfig launchConfigs[] = {
			{
				.binaryName	= "bin/debug/test_generate_vs_code_json",
				.debuggerType = VSCODE_DEBUGGER_TYPE_CPPDBG_GDB,
			},
			{
				.binaryName	= "bin/release/test_generate_vs_code_json",
				.debuggerType = VSCODE_DEBUGGER_TYPE_CPPDBG_GDB,
			},
		};

		VSCodeJSONOptions vsCodeOptions = {
			.cppPropertiesConfigs		= cppPropertiesConfigs,
			.cppPropertiesConfigsCount	= BUILDER_COUNT_OF( cppPropertiesConfigs ),
			.taskConfigs				= taskConfigs,
			.taskConfigsCount			= BUILDER_COUNT_OF( taskConfigs ),
			.launchConfigs				= launchConfigs,
			.launchConfigsCount			= BUILDER_COUNT_OF( launchConfigs ),
		};

		// generating the JSON is instead of building, not as well as, and Builder owns main() - so bail out here
		exit( Builder_GenerateVSCodeJSONFiles( options, &vsCodeOptions ) ? 0 : 1 );
	}
}
