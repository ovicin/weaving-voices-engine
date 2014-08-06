//
//  WeavingVoicesAttribute.cpp
//  ofWeavingVoices
//
//  Created by Ovidiu on 05/08/14.
//
//

#include "Attribute.h"

Attribute::Attribute(string name){
    data = NULL;
}
void Attribute::setData(string PublisherNetAddress,
                        float &data,
                        float TimeStamp){
    
    if(this->PublisherNetAddress != PublisherNetAddress){
        /* WARNING multiple publishers */
    }
    else {
        this->PublisherNetAddress = PublisherNetAddress;
    }
    this->data = (void*) &data;
    
    this->TimeStamp = TimeStamp;
}

void Attribute::setData(string &data){
    this->data = (void*) &data;
}

void* Attribute::getData(){
    return data;
}

void Attribute::addSubscriber(string subscriber){
    /* check if the subscriber doesn't already exists */
    if (find(Subscribers.begin(), Subscribers.end(), subscriber) != Subscribers.end()){
        /* add the subscriber to the vector */
        Subscribers.push_back(subscriber);
    }
}

void Attribute::removeSubscriber(string subscriber){
    vector<string>::iterator it;
    it = find(Subscribers.begin(), Subscribers.end(), subscriber);
    Subscribers.erase(it);
}