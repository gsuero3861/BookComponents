#include "pch.h" 


namespace BookReader
{  

	public enum class ItemContentManipulationState
	{
		Dislable,//this item is not being manipulating
		Enable	//this item is being manipulating
	};


	public delegate void ItemViewerContentUpdateStateEventHandler(Platform::Object^ sender , ItemContentManipulationState state);

	public ref class ItemViewerContent sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		ItemViewerContent();
		event ItemViewerContentUpdateStateEventHandler ^ OnItemViewerContentUpdateState ;
		property Platform::String^ ItemData
		{
			void set(Platform::String^ value){}
			Platform::String^ get(){ return nullptr ;}
		}

	private:

	};
}