// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package com.eprosima.idl.parser.exception;

import org.antlr.v4.runtime.RecognitionException;
import org.antlr.v4.runtime.Token;

public class ParseException extends RecognitionException
{
    public ParseException()
    {
        super("", null, null, null);
    }

    public ParseException(Token token, String message)
    {
        super(message, null, null, null);

        if(token != null)
            setOffendingToken(token);
    }
}
