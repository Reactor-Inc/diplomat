// generated by diplomat-tool
import wasm from "./diplomat-wasm.mjs";
import * as diplomatRuntime from "./diplomat-runtime.mjs";

const OptionString_box_destroy_registry = new FinalizationRegistry((ptr) => {
    wasm.OptionString_destroy(ptr);
});

export class OptionString {
    
    // Internal ptr reference:
    #ptr = null;

    // Lifetimes are only to keep dependencies alive.
    // Since JS won't garbage collect until there are no incoming edges.
    #selfEdge = [];
    
    #internalConstructor(symbol, ptr, selfEdge) {
        if (symbol !== diplomatRuntime.internalConstructor) {
            console.error("OptionString is an Opaque type. You cannot call its constructor.");
            return;
        }
        
        this.#ptr = ptr;
        this.#selfEdge = selfEdge;
        
        // Are we being borrowed? If not, we can register.
        if (this.#selfEdge.length === 0) {
            OptionString_box_destroy_registry.register(this, this.#ptr);
        }
        
        return this;
    }
    get ffiValue() {
        return this.#ptr;
    }

    static new_(diplomatStr) {
        let functionCleanupArena = new diplomatRuntime.CleanupArena();
        
        const diplomatStrSlice = functionCleanupArena.alloc(diplomatRuntime.DiplomatBuf.str8(wasm, diplomatStr));
        
        const result = wasm.OptionString_new(...diplomatStrSlice.splat());
    
        try {
            return result === 0 ? null : new OptionString(diplomatRuntime.internalConstructor, result, []);
        }
        
        finally {
            functionCleanupArena.free();
        }
    }

    write() {
        const write = new diplomatRuntime.DiplomatWriteBuf(wasm);
        
        const result = wasm.OptionString_write(this.ffiValue, write.buffer);
    
        try {
            return result === 0 ? null : write.readString8();
        }
        
        finally {
            write.free();
        }
    }

    borrow() {
        const diplomatReceive = new diplomatRuntime.DiplomatReceiveBuf(wasm, 9, 4, true);
        
        // This lifetime edge depends on lifetimes 'a
        let aEdges = [this];
        
        const result = wasm.OptionString_borrow(diplomatReceive.buffer, this.ffiValue);
    
        try {
            if (!diplomatReceive.resultFlag) {
                return null;
            }
            return new diplomatRuntime.DiplomatSliceStr(wasm, diplomatReceive.buffer,  "string8", aEdges).getValue();
        }
        
        finally {
            diplomatReceive.free();
        }
    }

    constructor(symbol, ptr, selfEdge) {
        return this.#internalConstructor(...arguments)
    }
}