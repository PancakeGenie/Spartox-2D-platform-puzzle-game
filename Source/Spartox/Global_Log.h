// Puzzle platformer game done by Vladimir Mokanj - 15.02.2021

#pragma once

#define GET_CLASSNAME_WITH_FUNCTION		FString(__FUNCTION__)
#define GET_LINE_NUMBER					FString::FromInt(__LINE__)

#define LOG(LogCategory, Message)		UE_LOG(LogCategory, Log, TEXT("%s [%s]: %s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message)) 