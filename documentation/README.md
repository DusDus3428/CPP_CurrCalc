# Software Design

This file contains all the documentation to CurrCalc's software design. This includes functional requirements, non-functional requirements, and architectural diagrams and descriptions.

## Table of Contents
1. **[Goal](#goal)**</br>
2. **[Rough Overview](#rough-overview)**</br>
3. **[Requirements](#requirements)**</br>
  3.1 **[Functional Requirements](#functional-requirements)**</br>
  3.2 **[Non-Functional Requirements](#non-functional-requirements)**</br>
4. **[Use Cases](#use-cases)**</br>
  4.1 **[Use Case Diagram](#use-case-diagram)**</br>
  4.2 **[Use Case Description](#use-case-description)**</br>
5. **[Class Diagram](#class-diagram)**</br>
6. **[Activity Diagrams](#activity-diagrams)**</br>

# Goal

CurrCalc is a C++ program, written in C++20, that converts an amount of money from one currency to another. The initial and target currencies as well as the amount are provided by the user, while the currency data is fetched from the [exchangerates API](https://exchangeratesapi.io/documentation/).

# Rough Overview

![CurrCalc Rough Overview](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/01_CurrCalc_RoughOverview.png "CurrCalc Rough Overview")

A user interacts with CurrCalc by selecting the initial and target currencies and specifying the conversion amount. 
CurrCalc requests currency data, like the list of available currencies and exchange rates from the external exchangesrates API. If everything goes well, the API will respond with a positive status code and the requested data or, in case of a failure, with just a status code. The REST protocol will be used in the communication between CurrCalc and the exchangerates API.

# Requirements

## Functional Requirements

| ID        	| Title                          | Description/Use Case (where possible)  														  |
| ------------- | ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| CurrCalc_FR_1 | Fetch Currencies 		 | CurrCalc should fetch the list of all available currencies from the exchangerates API, so a user is guaranteed up-to-date currency information. 	  |
| CurrCalc_FR_2 | Select Initial/Target Currency | As a user, I want to select the initial currency and target currency for the conversion from a numbered list, so I know what currencies are available. |
| CurrCalc_FR_3 | Specify Conversion Amount 	 | As a user, I want to type in the amount I would like to convert from the initial currency to the target one. |
| CurrCalc_FR_4 | Fetch Exchange Rates	 | CurrCalc should fetch exchange rates from the exchangerates API, so a user is guaranteed up-to-date exchange rates for the initial and target currencies. |
| CurrCalc_FR_5 | Convert Amount		 | CurrCalc should convert the specified amount from the selected initial currency to the selected target currency using the appropriate exchange rate fetched in CurrCalc_FR_4. |

## Non-Functional Requirements

| ID        	 | Title                          | Description																		   |
| -------------- | ------------------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------ |
| CurrCalc_NFR_1 | Do Not Store API Key In The Repository | The API key to the exchangerates API should not be stored in the online GitHub repository. 	  |
| CurrCalc_NFR_2 | Retry Failed REST Requests 	  | If the data retrieval requests specified in CurrCalc_FR_2 and CurrCalc_FR_4 return with status code 408, 425, 429, or 500, they should be retried three more times in intervals of three seconds. If no successful request can be processed after that, CurrCalc should terminate with an error message.   |
| CurrCalc_NFR_3 | Keep Precision of Five Fractional Digits For Conversion 	  | For the conversion an amount with a maximum of five fractional digits should be accepted. If the user inputs more than that, the amount should be rounded to five fractional digits.  |

# Use Cases

## Use Case Diagram

![CurrCalc Use Case Diagram](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/02_CurrCalc_UseCaseDiagram.png "CurrCalc Use Case Diagram")

There is only one possible use case when interacting with CurrCalc. The "Convert Currency" use case is triggered when the user starts the program, therefore the user is the primary actor. The exchangerates API is a secondary actor in this use case as CurrCalc must fetch the currency information from it.

## Use Case Description

<table>
	<tbody>
	<tr>
		<td>Title</td>
		<td>Convert Currency</td>
	</tr>
	<tr>
		<td>Description</td>
		<td>The user converts a specified amount from a selected initial currency to a selected target currency. The currency data is fetched from an external API.</td>
	</tr>
	<tr>
		<td>Actor(s)</td>
		<td>User, exchangerates API</td>
	</tr>
	<tr>
		<td>Goal</td>
		<td>Conversion of a specified amount of money from one currency into another using up-to-date currency data.</td>
	</tr>
	<tr>
		<td>Preconditions(s)</td>
		<td>CurrCalc has been started by the user.</td>
	</tr>
	<tr>
		<td>Basic Flow</td>
		<td>
			<ol type="1">
				<li>CurrCalc prints a welcome message for the user in the terminal.</li>
				<li>CurrCalc sends an HTTP GET request to the exchangerates API to retrieve Euro currency detail
					<ol type="i">
						<li>The API responds with a JSON object containing the currency detail for the Euro currency, including all exchange rates</li>
					</ol>
				</li>
				<li>CurrCalc outputs a numbered list of currencies, extracted from the Euro currency detail, and prompts the user to pick one for the initial currency
					<ol type="i">
						<li>The user types in the number of the desired initial currency
							<ol type="a">
								<li>CurrCalc confirms the selection</li>
							</ol>
						</li>
					</ol>
				</li>
				<li>CurrCalc outputs a numbered list of currencies, extracted from the Euro currency detail and excluding the initial currency, and prompts the user to pick one for the target currency
					<ol type="i">
						<li>The user types in the number of the desired target currency
							<ol type="a">
								<li>CurrCalc confirms the selection</li>
							</ol>
						</li>
					</ol>
				</li>
				<li>CurrCalc prompts the user to specify the conversion amount
					<ol type="i">
						<li>The user types in the desired amount as a decimal number
							<ol type="a">
								<li>CurrCalc confirms the selection</li>
							</ol>
						</li>
					</ol>
				</li>
				<li>CurrCal converts the specified amount from the initial currency into the target currency</li>
				<li>The program outputs the result of the calculation</li>
				<li>CurrCalc terminates</li>
			</ol>
		</td>
	</tr>
	<tr>
		<td>Post Condition(s)</td>
		<td>The specified amount has been converted from the selected initial currency to the selected target currency. CurrCalc program has been terminated.</td>
	</tr>
	<tr>
		<td>Alternative Flow(s)</td>
		<td>
			In 2.i: The API responds with a status code 408, 425, 429, or 500
			<ol type="1">
				<li>CurrCalc retries the request three more times in intervals of three seconds
					<ol type="i">
						<li>In case of a successful request (status code 200) CurrCalc continues - back to 2.i in basic flow</li>
						<li>In case all the attempts fail, CurrCalc informs the user of the situation and offers possible solutions
							<ol type="a">
								<li>CurrCalc terminates</li>
							</ol>
						</li>
					</ol>
				</li>
			</ol><br/>
			In 2.i: The API responds with a status code other than 200, 408, 425, 429, or 500
			<ol type="1">
				<li>CurrCalc informs the user of the situation and offers possible solutions
					<ol type="i">
						<li>CurrCalc terminates</li>
					</ol>
				</li>
			</ol><br/>
			In 3.i: The user types in an integer that is not on the list, a character, or a string
			<ol type="1">
				<li>CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 3 in basic flow</li>
			</ol><br/>
			In 3.i: The user types in a decimal number, whose whole number part is on the list
			<ol type="1">
				<li>The fractional part of the number is truncated - proceed with 3.i.a in basic flow</li>
			</ol><br/>
			In 3.i: The user types in a decimal number, whose whole number part is not on the list
			<ol type="1">
				<li>The fractional part of the number is truncated</li>
				<li>CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 3 in basic flow</li>
			</ol><br/>
			In 4.i: The user types in an integer that is not on the list, a character, or a string
			<ol type="1">
				<li>CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 4 in basic flow</li>
			</ol><br/>
			In 4.i: The user types in a decimal number, whose whole number part is on the list
			<ol type="1">
				<li>The fractional part of the number is truncated - proceed with 4.i.a in basic flow</li>
			</ol><br/>
			In 4.i: The user types in a decimal number, whose whole number part is not on the list
			<ol type="1">
				<li>The fractional part of the number is truncated</li>
				<li>CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 4 in basic flow</li>
			</ol><br/>
			In 5.i: The user types in a positive integer
			<ol type="1">
				<li>CurrCalc converts the integer into a decimal number and confirms the selection - proceed with 5.i.a in basic flow</li>
			</ol><br/>
			In 5.i: The user types in a negative decimal number, a negative integer, a character, or a string
			<ol type="1">
				<li>CurrCalc responds with a prompt to type in an unsigned number for the sum - back to 5.i in basic flow</li>
			</ol><br/>
		</td>
	</tbody>
</table>

# Class Diagram

![CurrCalc Class Diagram](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/03_CurrCalc_ClassDiagram.png "CurrCalc Class Diagram")

There are three classes: CurrencyDetail, ExchangeRate, and ExchangeratesApiClient.<br/> 
CurrencyDetail holds two public properties, a string called "name" for the name of the currency, and a list of ExchangeRate objects called "exchangeRates". The latter leads to a composition relationship from CurrencyDetail to ExchangeRate. CurrencyDetail also has the public "convertAmount" method, which takes a specified conversion amount, and the name of the target currency as arguments. The method will leverage the exchangeRates property to conduct the conversion.<br/>
ExchangeRate also holds two public properties, a string called "currencyName" for the name of the currency, and a double called "rate" for the actual exchange rate.<br/>
And then there is the ExchangeratesApiClient class. As its name states, it represents the client that sends requests to the exchangesrates API and handles the responses. It does not have any attributes, but four methods. The method getCurrencyNames() sends a request to the API to retrieve the list of currency names and then utilizes the private getCurrencyNamesFromResponse() method to extract and transform the names into a list of strings. Similarly, getCurrencyDetail() sends a request to the API to retrieve the currency detail using the name of the chosen initial currency. Then it utilizes the private getCurrencyDetailFromResponse() method to extract and transform the information into a CurrencyDetail object.

# Activity Diagrams

![CurrCalc Activity Diagram for Convert Currency](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/04_CurrCalc_ActivityDiagram_ConvertCurrency.png "CurrCalc Activity Diagram for Convert Currency")

The activity diagram above showcases the main flow of the program.<br/> 
Once CurrCalc is started, the program will send a REST request to the exchangerates API to retrieve the list of the names of available currencies. Once the API sends this to CurrCalc, the user must choose one of the currencies from the numbered list to use for the initial currency. If the user decides to make an input that is not one of the numbers on the list, they will be prompted to do so again until a valid selection has been made. This check is made within the Get Currency Selection activity.<br/>
After the selection has been made, CurrCalc uses it to request the full details of the currency, including the exchangerates for the other currencies. Once the API sends these to CurrCalc, the user is prompted to type in the amount that is to be converted. If the user types in something other than a positive integer or positive floating point number, they will be prompted to do so again until a valid number has been provided. Side note: positive integer numbers are converted into floating point numbers. This check is made within the Get Conversion Amount activity.<br/>
Next, the user must choose the target currency from a numbered list. The activity Get Currency Selection is reused here. The only difference is that the numbered list is gathered from the initial currency's exchange rates. This is done for two reasons: on one hand, we do not know if the API has all the exchange rates for the selected initial currency, and on the other, we do not need to include the initial currency.<br/>
Once this is done, the specified amount will be converted from the initial currency into the target one and the results will be printed to the console. Then the CurrCalc program is terminated. 

Please note that this is a very simplified activity diagram that displays the rough ideal flow of the program. All the possibilities of program termination are not depicted. However, they are described in the use case table **[here](#use-cases)**.