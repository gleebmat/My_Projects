
import {Fragment,memo,useCallback,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import DebounceInput from "react-debounce-input"
import {StateContexts,addEvents} from "$/utils/context"
import {TextArea as RadixThemesTextArea} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Debounceinput_debounceinput_947783dc41bb51e1045f619b53176859 = memo(({children}) => {
    const on_change_3872bfb7ba257a100be191b67e778076 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___chat____chat_state.set_input", ({ ["value"] : _e?.["target"]?.["value"] }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])
const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state)



    return(
        jsx(DebounceInput,{color:"teal",css:({ ["flex"] : "1", ["minHeight"] : "44px", ["maxHeight"] : "140px", ["background"] : "white" }),debounceTimeout:300,element:RadixThemesTextArea,onChange:on_change_3872bfb7ba257a100be191b67e778076,placeholder:"Ask about German grammar, vocabulary, or anything\u2026",resize:"none",size:"2",value:reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state.user_input_rx_state_},)
    )
});
