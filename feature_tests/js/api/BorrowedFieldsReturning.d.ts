// generated by diplomat-tool
import type { pointer, codepoint } from "./diplomat-runtime.d.ts";

type BorrowedFieldsReturning_obj = {
    bytes: string;
};



export class BorrowedFieldsReturning {
    
    get bytes() : string; 
    set bytes(value: string); 
    
    /** Create `BorrowedFieldsReturning` from an object that contains all of `BorrowedFieldsReturning`s fields.
    * Optional fields do not need to be included in the provided object.
    */
    static fromFields(structObj : BorrowedFieldsReturning_obj) : BorrowedFieldsReturning;


    constructor(structObj : BorrowedFieldsReturning_obj);
}