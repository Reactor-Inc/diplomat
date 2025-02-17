// generated by diplomat-tool
import type { DataProvider } from "./DataProvider"
import type { FixedDecimal } from "./FixedDecimal"
import type { FixedDecimalFormatterOptions } from "./FixedDecimalFormatterOptions"
import type { FixedDecimalFormatterOptions_obj } from "./FixedDecimalFormatterOptions"
import type { Locale } from "./Locale"
import type { pointer, codepoint } from "./diplomat-runtime.d.ts";


/** An  Fixed Decimal Format object, capable of formatting a [`FixedDecimal`] as a string.
*
*See the [Rust documentation for `FixedDecimalFormatter`](https://docs.rs/icu/latest/icu/decimal/struct.FixedDecimalFormatter.html) for more information.
*/


export class FixedDecimalFormatter {
    
    get ffiValue(): pointer;

    static tryNew(locale: Locale, provider: DataProvider, options: FixedDecimalFormatterOptions_obj): FixedDecimalFormatter | null;

    formatWrite(value: FixedDecimal): string;
}