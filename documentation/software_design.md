# Software Design

This file contains all the documentation to CurrCalc's design. This includes functional requirements, non-functional requirements, and architectural diagrams and descriptions.

# Requirements

## Functional Requirements

| ID        	| Title                          | Description/Use Case (where possible)  														  |
| ------------- | ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| CurrCalc_FR_1 | Fetch Currency Names 		 | CurrCalc should fetch the list of all available currencies from the exchangerates API, so a user is guaranteed up-to-date currency information. 	  |
| CurrCalc_FR_2 | Select Initial/Target Currency | As a user, I want to select the initial currency and target currency for the conversion from a numbered list, so I know what currencies are available. |
| CurrCalc_FR_3 | Specify Conversion Amount 	 | As a user, I want to type in the amount I would like to convert from the initial currency to the target one. |
| CurrCalc_FR_4 | Fetch Currency Details	 | CurrCalc should fetch the currency details for the initial currency from the exchangerates API, so a user is guaranteed up-to-date exchange rates for the currency. |
| CurrCalc_FR_5 | Convert Amount		 | CurrCalc should convert the specified amount from the selected initial currency to the selected target currency using the appropriate exchange rate fetched in CurrCalc_FR_4. |

## Non-Functional Requirements

| ID        	 | Title                          | Description																		   |
| -------------- | ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| CurrCalc_NFR_1 | Store API Key Using git-secret | The API key to the exchangereates API should be stored and encrypted in the repository using git-secret, to avoid storing sensitive data in a public online repository. 	  |
| CurrCalc_NFR_2 | Retry Failed REST Requests 	  | If the data retrieval requests specified in CurrCalc_FR_2 and CurrCalc_FR_4 return with a 500 or 503 status code, they should be retried three more times in intervals of three seconds. If no successful request can be processed after that CurrCalc should terminate.  |

# Architecture

## Rough Overview

![CurrCalc Rough Overview](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/01_CurrCalc-RoughOverview.png "CurrCalc Rough Overview")

The flow is as follows: a user interacts with the CurrCalc program by selecting the initial and target currencies and providing an amount that is to be converted. The list of available currency names and the details for the selected initial currency, which includes the currency rates, are requested from the external exchangesrates API. In case of a success, the API will respond with status code 200 and the requested data. The REST protocol will be used for the communication between CurrCalc and the exchangerates API.

## Use Cases

### Use Case Diagram

![CurrCalc Use Case Diagram](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/02_CurrCalc-UseCaseDiagram.png "CurrCalc Use Case Diagram")

There is only one possible use case when interacting with CurrCalc. The "Convert Currency" use case is triggered when the user starts the program, therefore the user is the primary actor. 
The exchangesrate API is a secondary actor in this use case as CurrCalc must fetch the currency information from it.

### Use Case Descriptions

| Title 				| 	Convert Currency |
| Description 			| 	The user selects the initial and target currencies, and types in an amount. Then CurrCalc converts the amount from the initial currency into the target currency. The currency information is fetched from an external API. |
| Actor(s) 				| 	User, exchangereates API |
| Goal 					| 	Conversion of a specified amount of money from one currency into another using up-to-date currency data. |
| Precondition(s) 		| 	CurrCalc has been started by the user. |
| Basic Flow 			| 	1. CurrCalc sends a HTTP GET request to the exchangerates API to retrieve the list of available currency names
								- a. The API responds with a JSON file containing names of all available currencies
							2. CurrCalc outputs a numbered list of currency names and prompts the user to pick one for the initial currency
	        					- a. The user types in the number of the desired initial currency
	                				- i. CurrCalc confirms the selection
							3. CurrCalc sends a HTTP GET request to the exchangerates API to retrieve the details to the initial currency
	        					- a. The API responds with a JSON file containing the details to the initial currency, including the exchange rates
							4. CurrCalc prompts the user to specify the amount that is to be converted
	        					- a. The user types in the desired amount as a decimal number
	                				- i. CurrCalc confirms the selection
							5. CurrCalc outputs a numbered list of currency names and prompts the user to pick one for the target currency
	        					- a. The user types in the number of the desired target currency
	                				- i. CurrCalc confirms the selection
							6. CurrCal converts the specified amount from the initial currency into the target currency
							7. The program outputs the result of the calculation
							8. CurrCalc terminates |
| Post Condition(s) 	| Conversion has been completed. CurrCalc program has been terminated. |
| Alternative Flow(s)	| 	In 1.a: The API responds with a status code 500 or 503
	        					- a. CurrCalc retries the request three more times in intervals of three seconds
	                				- i. In case of a successful request (status code 200) CurrCalc continues - back to 1.a in basic flow
	                				- ii. In case all the attempts fail, CurrCalc informs the user of the situation and offers possible solutions
	                        			- i. CurrCalc terminates
	
							In 1.a: The API responds with a status code other than 200, 500, or 503
	        					- a. CurrCalc informs the user of the situation and offers possible solutions
	                				- i. CurrCalc terminates
	
							In 2.a: The user types in an integer that is not on the list, a decimal number, a character, or a string
	        					- a. CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 2 in basic flow
	
							In 3.a: The API responds with a status code 404
	        					- a. CurrCalc retries the request three more times in intervals of three seconds
	                				- i. In case of a successful request (status code 200) CurrCalc continues - back to 3.a in basic flow
	                				- ii. In case all the attempts fail, CurrCalc informs the user of the situation and offers possible solutions
	                        			- i. CurrCalc terminates
	
							In 3.a: The API responds with a status code other than 200 and 404
	        					- a. CurrCalc informs the user of the situation and offers possible solutions
	                				- i. CurrCalc terminates
	
							In 4.a: The user types in a positive integer 
	        					- a. CurrCalc converts the integer into a decimal number and confirms the selection - proceed with 4.a.a in basic flow
	
							In 4.a: The user types in a negative decimal number, a negative integer, a character, or a string
	        					- a. CurrCalc responds with a prompt to type in an unsigned number for the sum - back to 4.a in basic flow
	
							In 5.a: The user types in an integer that is not on the list, a decimal number, a character, or a string
	        					- a. CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 5 in basic flow |
