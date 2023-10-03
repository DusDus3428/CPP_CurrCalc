# Software Design

This file contains all the documentation to CurrCalc's design. This includes functional requirements, non-functional requirements, and architectural diagrams and descriptions.

## Table of Contents
1. **[Premise](#premise)**</br>
2. **[Requirements](#requirements)**</br>
  2.1 **[Functional Requirements](#functional-requirements)**</br>
  2.2 **[Non-Functional Requirements](#non-functional-requirements)**</br>
3. **[Architecture](#architecture)**</br>
  3.1 **[Rough Overview](#rough-overview)**</br>
  3.2 **[Use Cases](#use-cases)**</br>
  3.3 **[Class Diagram](#class-diagram)**</br>
  3.4 **[Activity Diagram](#activity-diagram)**</br>

# Premise

CurrCalc is a C++ program written in C++20. To begin with it will remain strictly a console application. 

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

![CurrCalc Rough Overview](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/01_CurrCalc_RoughOverview.png "CurrCalc Rough Overview")

The flow is as follows: a user interacts with the CurrCalc program by selecting the initial and target currencies and providing an amount that is to be converted. The list of available currency names and the details for the selected initial currency, which includes the currency rates, are requested from the external exchangesrates API. In case of a success, the API will respond with status code 200 and the requested data. The REST protocol will be used for the communication between CurrCalc and the exchangerates API.

## Use Cases

### Use Case Diagram

![CurrCalc Use Case Diagram](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/02_CurrCalc_UseCaseDiagram.png "CurrCalc Use Case Diagram")

There is only one possible use case when interacting with CurrCalc. The "Convert Currency" use case is triggered when the user starts the program, therefore the user is the primary actor. The exchangesrate API is a secondary actor in this use case as CurrCalc must fetch the currency information from it.
Here is a classical use case description for the Convert Currency use case:

<table>
  <tr>
    <td>Title</td>
    <td>Convert Currency</td>
  </tr>
  <tr>
    <td>Description</td>
    <td>The user selects the initial and target currencies, and types in an amount. Then CurrCalc converts the amount from the initial currency into the target currency. The currency information is fetched from an external API.</td>
  </tr>
  <tr>
    <td>Actor(s)</td>
    <td>User, exchangereates API</td>
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
			<li>CurrCalc sends a HTTP GET request to the exchangerates API to retrieve the list of available currency names
				<ol type="i">
					<li>The API responds with a JSON file containing names of all available currencies</li>
				</ol>
			</li>
			<li>CurrCalc outputs a numbered list of currency names and prompts the user to pick one for the initial currency
				<ol type="i">
					<li>The user types in the number of the desired initial currency
						<ol type="a">
							<li>CurrCalc confirms the selection</li>
						</ol>
					</li>
				</ol>
			</li>
			<li>CurrCalc sends a HTTP GET request to the exchangerates API to retrieve the details to the initial currency
				<ol type="i">
					<li>The API responds with a JSON file containing the details to the initial currency, including the exchange rates</li>
				</ol>
			</li>
			<li>CurrCalc prompts the user to specify the amount that is to be converted
				<ol type="i">
					<li>The user types in the desired amount as a decimal number
						<ol type="a">
							<li>CurrCalc confirms the selection</li>
						</ol>
					</li>
				</ol>
			</li>
			<li>CurrCalc outputs a numbered list of currency names and prompts the user to pick one for the target currency
				<ol type="i">
					<li>The user types in the number of the desired target currency
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
    <td>Conversion has been completed. CurrCalc program has been terminated.</td>
  </tr>
  <tr>
    <td>Alternative Flow(s)</td>
	<td>
		In 1.i: The API responds with a status code 500 or 503
		<ol type="1">
			<li>CurrCalc retries the request three more times in intervals of three seconds
				<ol type="i">
					<li>In case of a successful request (status code 200) CurrCalc continues - back to 1.i in basic flow</li>
					<li>In case all the attempts fail, CurrCalc informs the user of the situation and offers possible solutions
						<ol type="a">
							<li>CurrCalc terminates</li>
						</ol>
					</li>
				</ol>
			</li>
		</ol><br/>
		In 1.i: The API responds with a status code other than 200, 500, or 503
		<ol type="1">
			<li>CurrCalc informs the user of the situation and offers possible solutions
				<ol type="i">
					<li>CurrCalc terminates</li>
				</ol>
			</li>
		</ol><br/>
		In 2.i: The user types in an integer that is not on the list, a decimal number, a character, or a string
		<ol type="1">
			<li>CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 2 in basic flow</li>
		</ol><br/>
		In 3.i: The API responds with a status code 500 or 503
		<ol type="1">
			<li>CurrCalc retries the request three more times in intervals of three seconds
				<ol type="i">
					<li>CurrCalc retries the request three more times in intervals of three seconds</li>
					<li>In case all the attempts fail, CurrCalc informs the user of the situation and offers possible solutions
						<ol type="a">
							<li>CurrCalc terminates</li>
						</ol>
					</li>
				</ol>
			</li>
		</ol><br/>
		In 3.i: The API responds with a status code other than 200, 500, or 503
		<ol type="1">
			<li>CurrCalc informs the user of the situation and offers possible solutions
				<ol type="i">
					<li>CurrCalc terminates</li>
				</ol>
			</li>
		</ol><br/>
		In 4.i: The user types in a positive integer
		<ol type="1">
			<li>CurrCalc converts the integer into a decimal number and confirms the selection - proceed with 4.i.a in basic flow</li>
		</ol><br/>
		In 4.i: The user types in a negative decimal number, a negative integer, a character, or a string
		<ol type="1">
			<li>CurrCalc responds with a prompt to type in an unsigned number for the sum - back to 4.i in basic flow</li>
		</ol><br/>
		In 5.i: The user types in an integer that is not on the list, a decimal number, a character, or a string
		<ol type="1">
			<li>CurrCalc responds with a prompt to make a selection based on the numbers provided in the list - back to 5 in basic flow</li>
		</ol>
	</td>
</table>

## Class Diagram

![CurrCalc Class Diagram](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/03_CurrCalc_ClassDiagram.png "CurrCalc Class Diagram")

There are three classes: CurrencyDetail, ExchangeRate, and ExchangeratesApiClient.<br/> 
CurrencyDetail holds two public properties, a string called "name" for the name of the currency, and a list of ExchangeRate objects called "exchangeRates". The latter leads to a composition relationship from CurrencyDetail to ExchangeRate. CurrencyDetail also has the public "convertAmount" method, which takes a specified conversion amount, and the name of the target currency as arguments. The method will leverage the exchangeRates property to conduct the conversion.<br/>
ExchangeRate also holds two public properties, a string called "currencyName" for the name of the currency, and a double called "rate" for the actual exchange rate.<br/>
And then there is the ExchangeratesApiClient class. As its name states, it represents the client that sends requests to the exchangesrates API and handles the responses. It does not have any attributes, but four methods. The method getCurrencyNames() sends a request to the API to retrieve the list of currency names and then utilizes the private getCurrencyNamesFromResponse() method to extract and transform the names into a list of strings. Similarly, getCurrencyDetail() sends a request to the API to retrieve the currency detail using the name of the chosen initial currency. Then it utilizes the private getCurrencyDetailFromResponse() method to extract and transform the information into a CurrencyDetail object.

## Activity Diagram

![CurrCalc Activity Diagram for Convert Currency](https://github.com/DusDus3428/CPP_CurrCalc/blob/feature/01_design/documentation/images/diagrams/04_CurrCalc_ActivityDiagram_ConvertCurrency.png "CurrCalc Activity Diagram for Convert Currency")

The activity diagram above showcases the main flow of the program.<br/> 
Once CurrCalc is started, the program will send a REST request to the exchangerates API to retrieve the list of the names of available currencies. Once the API sends this to CurrCalc, the user must choose one of the currencies from the numbered list to use for the initial currency. If the user decides to make an input that is not one of the numbers on the list, they will be prompted to do so again until a valid selection has been made.<br/>
After the selection has been made, CurrCalc uses it to request the full details of the currency, including the exchangerates for the other currencies. Once the API sends these to CurrCalc, the user is prompted to type in the amount that is to be converted. If the user types in something other than a positive integer or positive floating point number, they will be prompted to do so again until a valid number has been provided. Side note: positive integer numbers are converted into floating point numbers.<br/>
Next, the user must choose the target currency from a numbered list. This list is gathered from the initial currency's exchange rates. If the user decides to make a selection that is not one of the numbers on the list, they will be prompted to do so again until a valid selection has been made.<br/>
Once this is done, the specified amount will be converted from the initial currency into the target one and the results will be printed to the console. Then the CurrCalc program is terminated. 