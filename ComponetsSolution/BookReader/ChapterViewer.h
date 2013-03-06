#include "pch.h" 

namespace BookReader
{
	public ref class ChapterViewer sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		ChapterViewer();
		void LoadBook();

		property Platform::Object^ DataSource
		{
			void set(Platform::Object^ value)
			{
				this->_datasource = (BookData::ChapterDataSource ^)value ;
				this->_textelement->DataSource = _datasource->Text ;
				this->_videoelement->DataSource = _datasource->Video ;
				this->_pageselement->DataSource = _datasource->Pages ;
				this->_galleryelement->DataSource = _datasource->Gallery ;
			}
			Platform::Object^ get(){ return this->_datasource ; }
		}

	private:
		Windows::UI::Xaml::Controls::StackPanel^ _elementspanel ;
		TextView ^ _textelement;
		VideoView ^ _videoelement;
		void initelements();
		BookData::ChapterDataSource ^ _datasource ;
		
		
#pragma region Text Element
#pragma endregion
		
#pragma region Video Element
#pragma endregion 
		
#pragma region Pages Element
	public: 

		property float64 ThumbPageWidth
		{
			void set(float64 value){ this->_pageselement->StackViewItemWidth =  value ; }
			float64 get(){ return this->_pageselement->StackViewItemWidth ; }
		}

		property float64 ThumbPageHeight
		{
			void set(float64 value){ this->_pageselement->StackViewItemHeight =  value ; }
			float64 get(){ return this->_pageselement->StackViewItemHeight ; }
		}

		property float64 ThumbPageSeparation
		{
			void set(float64 value){ this->_pageselement->DeltaItemSeparation =  value; }
			float64 get(){ return this->_pageselement->DeltaItemSeparation ; }
		}

		property float64 PageWidth
		{
			void set(float64 value){ this->_pageselement->FullSreenItemWidth =value ; }
			float64 get(){ return this->_pageselement->FullSreenItemWidth ; }
		}

		property float64 PageHeight
		{
			void set(float64 value){ this->_pageselement->FullSreenItemHeight = value ; }
			float64 get(){ return this->_pageselement->FullSreenItemHeight ; }
		}

		property float64 PageTranslationX
		{
			void set(float64 value){ this->_pageselement->FullScreenX = value  ; }
			float64 get(){ return this->_pageselement->FullScreenX ; }
		}

		property float64 PageTranslationY
		{
			void set(float64 value){ this->_pageselement->FullScreenY = value  ; }
			float64 get(){ return this->_pageselement->FullScreenY ; }
		}


	private:
		
		StackView ^ _pageselement ;
#pragma endregion
		
#pragma region Gallery Element
	private:
		StackView ^ _galleryelement ;

	public:
		/**
		property Windows::Foundation::Collections::IVector<Platform::String^>^ GalleryThumbList
		{
			void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
			{ this->_galleryelement->ThumbItemsList = value ;	}
			Windows::Foundation::Collections::IVector<Platform::String^>^ get()
			{ return this->_galleryelement->ThumbItemsList ;}
		};

		property Windows::Foundation::Collections::IVector<Platform::String^>^ GalleryMediumList
		{
			void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
			{ this->_galleryelement->MediumItemsList = value ;	}
			Windows::Foundation::Collections::IVector<Platform::String^>^ get()
			{ return this->_galleryelement->MediumItemsList ;}
		};

		property Windows::Foundation::Collections::IVector<Platform::String^>^ GalleryFullScreenList
		{
			void set(Windows::Foundation::Collections::IVector<Platform::String^>^ value)
			{ this->_galleryelement->FullScreenItemsList = value ;	}
			Windows::Foundation::Collections::IVector<Platform::String^>^ get()
			{ return this->_galleryelement->FullScreenItemsList ;}
		};
		*/

		property float64 ThumbGalleryWidth
		{
			void set(float64 value){ this->_galleryelement->StackViewItemWidth = value ; }
			float64 get(){ return this->_galleryelement->StackViewItemWidth ; }
		}

		property float64 ThumbGalleryHeight
		{
			void set(float64 value){ this->_galleryelement->StackViewItemHeight = value ; }
			float64 get(){ return this->_galleryelement->StackViewItemHeight ; }
		}

		property float64 ThumbGallerySeparation
		{
			void set(float64 value){ this->_galleryelement->DeltaItemSeparation = value ; }
			float64 get(){ return this->_galleryelement->DeltaItemSeparation ; }
		}

		//full screen
		property float64 GalleryWidth
		{
			void set(float64 value){ this->_galleryelement->FullSreenItemWidth= value  ; }
			float64 get(){ return this->_galleryelement->FullSreenItemWidth ; }
		}

		//full screen
		property float64 GalleryHeight
		{
			void set(float64 value){ this->_galleryelement->FullSreenItemHeight = value ; }
			float64 get(){ return this->_galleryelement->FullSreenItemHeight ; }
		}

		//translation when full screen
		property float64 GalleryTranslationX
		{
			void set(float64 value){ this->_galleryelement->FullScreenX = value ; }
			float64 get(){ return this->_galleryelement->FullScreenX ; }
		}

		//translation when full screen
		property float64 GalleryTranslationY
		{
			void set(float64 value){ this->_galleryelement->FullScreenY = value ; }
			float64 get(){ return this->_galleryelement->FullScreenY ; }
		}
#pragma endregion


	};
}