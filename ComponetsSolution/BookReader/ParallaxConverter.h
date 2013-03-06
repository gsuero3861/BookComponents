#include "pch.h"
using namespace Windows::UI::Xaml::Interop;
using namespace Platform ;
using namespace Windows::UI::Xaml::Data ;

namespace BookReader
{

	static const float64 _factor = 0.10 ;


	public ref class  ParallaxConverter sealed : Windows::UI::Xaml::Data::IValueConverter
	{
	public:
		virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
        virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		
	};
}