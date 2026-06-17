
import {Fragment,memo,useCallback,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isNotNullOrUndefined,isTrue} from "$/utils/state"
import DebounceInput from "react-debounce-input"
import {StateContexts,addEvents} from "$/utils/context"
import {TextField as RadixThemesTextField} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Debounceinput_debounceinput_371ae9266e07684acc69c9fbc4179e58 = memo(({children}) => {
    const on_change_186bf989b8bcf76f57be4b4671717a96 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___translation____translation_state.set_word", ({ ["value"] : _e?.["target"]?.["value"] }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])
const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state)



    return(
        jsx(DebounceInput,{color:"teal",css:({ ["flex"] : "1", ["background"] : "white" }),debounceTimeout:300,element:RadixThemesTextField.Root,onChange:on_change_186bf989b8bcf76f57be4b4671717a96,placeholder:"Enter a German or English word\u2026",size:"3",value:(isNotNullOrUndefined(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state.word_rx_state_) ? reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___translation____translation_state.word_rx_state_ : "")},)
    )
});
