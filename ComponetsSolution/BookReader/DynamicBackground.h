#include "pch.h" 

namespace BookReader
{
	public ref class DynamicBackground sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		DynamicBackground();

		property Platform::String^ SourcePath
		{
			void set(Platform::String^ value)
			{
				this->_backgroundsource = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(ref new Windows::Foundation::Uri(value));
				for (int i = 0; i < this->_backgroundcontainer->Children->Size; i++)
					((Windows::UI::Xaml::Controls::Image^)this->_backgroundcontainer->Children->GetAt(i))->Source = this->_backgroundsource ;
			}
			Platform::String^ get()
			{ return nullptr ; }
		}

		property  float64 ItemHeight
		{
			void set(float64 value)
			{
				this->_itemheight = value ;
				for (int i = 0; i < this->_backgroundcontainer->Children->Size; i++)
					((Windows::UI::Xaml::Controls::Image^)this->_backgroundcontainer->Children->GetAt(i))->Height = this->_itemheight;
			}
			float64 get(){return this->_itemheight ;}
		}

		property  float64 ItemWidht
		{
			void set(float64 value){ 
				this->_itemwidth =  value ; 
				for (int i = 0; i < this->_backgroundcontainer->Children->Size; i++)
					((Windows::UI::Xaml::Controls::Image^)this->_backgroundcontainer->Children->GetAt(i))->Width  =  this->_itemwidth;
			}
			float64 get(){return this->_itemwidth ;}
		}

		property  float64 BackgroundWidth
		{
			void set(float64 value)
			{ 
				_backgroundwidth =  value ; 
				setbackgroundsize();
			}
			float64 get(){return this->_backgroundwidth ;}
		}

	private:
		Windows::UI::Xaml::Controls::StackPanel ^ _backgroundcontainer ;
		Windows::UI::Xaml::Media::Imaging::BitmapImage ^ _backgroundsource ;
		int32 _numberofitems ;
		float64 _itemheight, _itemwidth, _backgroundwidth ;

		void setbackgroundsize();

	};
}