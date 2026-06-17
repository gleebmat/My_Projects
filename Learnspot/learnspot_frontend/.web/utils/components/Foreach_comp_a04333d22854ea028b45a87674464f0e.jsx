
import {Fragment,memo,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {StateContexts,addEvents} from "$/utils/context"
import {Box as RadixThemesBox,Text as RadixThemesText} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Foreach_comp_a04333d22854ea028b45a87674464f0e = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state.conversations_rx_state_ ?? [],((conv_rx_state_,index_2fd64e0b86e85453f345ee553e7ed9af)=>(jsx(RadixThemesBox,{css:({ ["padding"] : "0.55rem 0.75rem", ["borderRadius"] : "0.5rem", ["cursor"] : "pointer", ["background"] : ((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state.active_conv_id_rx_state_?.valueOf?.() === conv_rx_state_?.["id"]?.valueOf?.()) ? "rgba(1,105,111,0.08)" : "transparent"), ["border"] : ((reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___chat____chat_state.active_conv_id_rx_state_?.valueOf?.() === conv_rx_state_?.["id"]?.valueOf?.()) ? "1px solid rgba(1,105,111,0.2)" : "1px solid transparent"), ["transition"] : "all 180ms ease", ["&:hover"] : ({ ["background"] : "rgba(1,105,111,0.08)" }), ["width"] : "100%" }),key:index_2fd64e0b86e85453f345ee553e7ed9af,onClick:((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___chat____chat_state.select_conversation", ({ ["cid"] : conv_rx_state_?.["id"] }), ({  })))], [_e], ({  }))))},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.82rem", ["color"] : "#28251d", ["overflow"] : "hidden", ["textOverflow"] : "ellipsis", ["whiteSpace"] : "nowrap", ["fontWeight"] : "500" })},conv_rx_state_?.["title"])))))
    )
});
