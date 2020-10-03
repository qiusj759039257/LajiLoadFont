#include <Windows.h>
#include <wingdi.h>
#include <fstream>

#include "avisynth.h"

class LajiLoadFont : public GenericVideoFilter
{
public:
	LajiLoadFont(PClip _child, const char* filename, IScriptEnvironment* env);
	~LajiLoadFont();
	PVideoFrame __stdcall GetFrame(int n, IScriptEnvironment* env);
private:
	const char * filename;
};

LajiLoadFont::LajiLoadFont(PClip _child, const char * filename, IScriptEnvironment* env) : GenericVideoFilter(_child), filename(filename)
{
	std::ifstream ifile(filename);

	if (!ifile)
	{
		env->ThrowError("Font file not found");
	}

	ifile.close();

	AddFontResourceExA(filename, FR_PRIVATE, 0);
}

LajiLoadFont::~LajiLoadFont()
{
	RemoveFontResourceExA(filename, FR_PRIVATE, 0);
}

PVideoFrame __stdcall LajiLoadFont::GetFrame(int n, IScriptEnvironment* env)
{
	return child->GetFrame(n, env);
};

AVSValue __cdecl Create_LajiLoadFont(AVSValue args, void* user_data, IScriptEnvironment* env)
{
	return new LajiLoadFont(args[0].AsClip(), args[1].AsString(), env);
}

const AVS_Linkage* AVS_linkage = 0;

extern "C" __declspec(dllexport) const char* __stdcall AvisynthPluginInit3(IScriptEnvironment * env, const AVS_Linkage* const vectors)
{
	AVS_linkage = vectors;
	env->AddFunction("LajiLoadFont", "cs", Create_LajiLoadFont, 0);
	return "Load a font";
}
