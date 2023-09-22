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
| CurrCalc_NFR_2 | Retry Failed REST Requests 	  | If the data retrieval requests specified in CurrCalc_FR_2 and CurrCalc_FR_4 return with a 500 or 503 status code, they should be retried three more times in intervals of three seconds. If no successful request can be processed after that, CurrCalc should terminate.  |

# Architecture

## Rough Overview

![CurrCalc Rough Overview](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/01_CurrCalc-RoughOverview.png "CurrCalc Rough Overview")

Since our solution will be fairly simple and small, I decided against using a UML diagram. I couldn't find one that fit the scale and structure I was striving for. If you have an suggestions, please let me know in the comment section. But for now, this general overview should suffice.
The flow is relatively simple: a user interacts with the CurrCal program by selecting the initial and target currencies and providing a sum that is to be converted. The list of available currencies and the various exchange rates are requested from the external exchangesrates API. If everything goes well, the API will respond with a positive status code and the requested data or, in case of a failure, with just a status code. The REST protocol will be used in the communication between CurrCal and the API.