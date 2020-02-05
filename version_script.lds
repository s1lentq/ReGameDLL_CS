REGAMEDLL_ABI_1.0 {
	global:
		*;
	local:
		_Zn*;
		_Zd*;

		extern "C++" {
			*std::*;
			*__cxxabi*::*;
			*__gnu_cxx::*;
			__cxa_*;
			_txnal_*;
			__dynamic_cast;
			__gxx_personality_*;
			__gcclibcxx_demangle_callback;
		};
};
