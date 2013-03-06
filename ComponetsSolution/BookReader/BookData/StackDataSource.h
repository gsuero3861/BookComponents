#include "pch.h"

namespace BookReader
{
	namespace BookData
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class StackDataSource sealed : public BookReader::BookData::BindableSourceBase
		{
		public:
			StackDataSource();

			property Windows::Foundation::Collections::IVector<Platform::String^> ^ ThumbsList
			{
				void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value){ this->_thumbslist = value ; }
				Windows::Foundation::Collections::IVector<Platform::String^> ^ get(){ return this->_thumbslist ; }
			}

			property Windows::Foundation::Collections::IVector<Platform::String^> ^ MediumList
			{
				void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value){ this->_mediumlist = value ; }
				Windows::Foundation::Collections::IVector<Platform::String^> ^ get(){ return this->_mediumlist ; }
			}

			property Windows::Foundation::Collections::IVector<Platform::String^> ^ FullPageList
			{
				void set(Windows::Foundation::Collections::IVector<Platform::String^> ^ value){ this->_fullpagelist = value ; }
				Windows::Foundation::Collections::IVector<Platform::String^> ^ get(){ return this->_fullpagelist ; }
			}

		private:
			Windows::Foundation::Collections::IVector<Platform::String^> ^ _thumbslist ;
			Windows::Foundation::Collections::IVector<Platform::String^> ^ _mediumlist ;
			Windows::Foundation::Collections::IVector<Platform::String^> ^ _fullpagelist ;
		};
	}
}