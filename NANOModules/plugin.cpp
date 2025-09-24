#include "plugin.hpp"

Plugin *pluginInstance;

void init(Plugin *p)
{
    pluginInstance = p;

    // Add modules here
    p->addModel(modelMAR);
    p->addModel(modelFONT);
    p->addModel(modelALT);
    p->addModel(modelQUART);
    p->addModel(modelONA);
    p->addModel(modelSERRA); 
    p->addModel(modelCEQ);    
    p->addModel(modelSTMAR); 
    p->addModel(modelPerformanceMixer); 
    p->addModel(modelVCVRANDOM);    
    p->addModel(modelEXP4);    
    p->addModel(modelARC);    
    p->addModel(modelSTFONT);    
    p->addModel(modelOCTA);    
    // p->addModel(modelBLANK12Hp);
    // p->addModel(modelBLANK8Hp);
    // p->addModel(modelBLANK6Hp);
    // p->addModel(modelBLANK4Hp);
    // p->addModel(modelBLANK2Hp);
}
