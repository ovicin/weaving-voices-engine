//
//  WeavingVoicesService.cpp
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#include "Subscriber.h"

Subscriber::Subscriber(){

    

    
}

void Subscriber::init(string ServiceName, string LocalAddress, string BroadCastAddress){
    this->LocalAddress = LocalAddress;
    this->BroadCastAddress = BroadCastAddress;
    this->ServiceName = ServiceName;
}

void Subscriber::put(Attribute &attribute){

}

void Subscriber::subscribe(Attribute &attribute){
    
}

void Subscriber::unsubscribe(Attribute &attribute){
    
}

void Subscriber::updateCallback(){
}
