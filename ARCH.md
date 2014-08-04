Weaving Voices Engine
=====================

##Architecture

This document is a draft on the software architecture for the Weaving Voices Engine. The design emphazise a multi-peer but yet simple and flexible design.

###Attributes dictionary

This Attributed dictionary defines the main **data model** used:

* Name
* Value
* Net Adress
* Subscribers

###Actors

####Service

Services are instances running some logic or view, they communicate using a subscription based model.

#####Attributes actions:


	* **PUT:** Updates an attribute locally and remotley.
 
		* Properties:
			* Name
			* Value
		
		* Actions:
			* Update the **Arbiter attributes dictionary**
			* Update the **Local attributes dictionary**
	
	* **SUBSCRIBERS:** Subscribes to an attribute locally or remotley.
 
		* Properties:
			* Attribute Name
		
		* Actions:
			* Updates the **Subscribers** for a particular **Name** on the **Arbiter attributes dictionary** 
			* Return the current **Value** for the particular **Name**



####Publisher

The publisher is the subscription manager and updates pusher.

#####Attributes actions:

	* **PUBLISH:** Pushes updates on the **Arbiter attributes dictionary** to the registered **Services**.
 			
		* Trigger:
			* An update on the **Arbiter attributes dictionary**.
		
		* Actions:
			* Pushes the updates on the **Arbiter attributes dictionary** to the **Subscribers** for an specific **Attribute**.