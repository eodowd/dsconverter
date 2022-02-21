#include "UltraEngine.h"

using namespace UltraEngine;

int main(int argc, const char* argv[])
{
    auto plugin = LoadPlugin("Plugins/FITextureLoader.*");
    if (plugin == NULL)
    {
        Print("Failed to load FreeImage plugin.");
        return 0;
    }


    auto displays = GetDisplays();
    

    auto window = CreateWindow("dsconverter", 0, 0, 640, 480, displays[0], WINDOW_TITLEBAR | WINDOW_CENTER);


    auto ui = CreateInterface(window);
    auto textarea = CreateLabel("", 30, 410, 640, 30, ui->root);
    
    

    int x = (window->ClientSize().x - 250) / 2;
    int y = (window->ClientSize().y - 60) / 2;
    auto button = CreateButton("Open File", x, y+80, 250, 60, ui->root);
    //Create a pixmap
    auto logo = LoadPixmap("dssa.png");
    
    //Show the icon
    ui->root->SetPixmap(logo);
    auto combobox = CreateListBox(x, y-10, 250, 73, ui->root);
    combobox->AddItem("Convert from .dspreset to .SFZ",true);
    combobox->AddItem("Convert from .txprog to .dspreset");
    combobox->AddItem("Validate a .dspreset");
    textarea->SetText("v0.0.1-alpha");
        
    while (true)
    {
        const Event ev = WaitEvent();
        switch (ev.id)
        {
        case EVENT_WINDOWCLOSE:
            return 0;
            break;
        case EVENT_WIDGETACTION:
            if(combobox->GetSelectedItem() == 0 && ev.source == button){
                WString file = RequestFile("Open File", "", "dspreset(*.dspreset):dspreset", 0, false);
                if(file != ""){
                    WString filepath = RequestDir("Save File");
                        if(filepath != ""){
                            Notify(Command("python main.py " + file.ToString() + " " + filepath.ToString()));
                            }
                        else{
                            Notify("File path not selected");
                            }
                        }
                else{
                    Notify("No file preset selected");
                  
                    }
                
            }else if(combobox->GetSelectedItem() == 1 && ev.source == button){//print other
                Notify("Not working yet 1");//end
               
            }else if(combobox->GetSelectedItem() == 2 && ev.source == button){//print other
                Notify("Not working yet 2");//end
            }
            
                
            break;
        case EVENT_WIDGETSELECT:
            break;
        }
    }
    return 0;
}
