#include "pch.h" 


namespace BookReader
{

	public delegate void ItemViewerContentManipulationStartedEventHandler(Platform::Object^ sender , int32 item);
	public delegate void ItemViewerContentManipulationFinishedEventHandler(Platform::Object^ sender , int32 item);
	public delegate void ItemViewerContentUpdateStateEventHandler();

	public ref class ItemViewerContent sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		ItemViewerContent();
		event ItemViewerContentUpdateStateEventHandler ^ OnItemViewerContentUpdateState ;
		property Platform::String^ DataItem
		{
			void set(Platform::String^ value){}
			Platform::String^ get(){ return nullptr ;}
		}

	private:

	};
}