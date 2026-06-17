
import {Fragment,memo,useCallback,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import DebounceInput from "react-debounce-input"
import {StateContexts,addEvents} from "$/utils/context"
import {TextArea as RadixThemesTextArea} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Debounceinput_debounceinput_8d6d32647700d2d235ae29a958cf0e50 = memo(({children}) => {
    const on_change_d418c6c9726e5b04c5115364883e9cd4 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___texts____text_state.set_input", ({ ["value"] : _e?.["target"]?.["value"] }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])
const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state)



    return(
        jsx(DebounceInput,{color:"teal",css:({ ["minHeight"] : "140px", ["width"] : "100%", ["background"] : "white" }),debounceTimeout:300,element:RadixThemesTextArea,onChange:on_change_d418c6c9726e5b04c5115364883e9cd4,placeholder:"Ich habe gestern ein buch gelesen und es war sehr interessant\u2026",size:"3",value:reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state.input_text_rx_state_},)
    )
});
