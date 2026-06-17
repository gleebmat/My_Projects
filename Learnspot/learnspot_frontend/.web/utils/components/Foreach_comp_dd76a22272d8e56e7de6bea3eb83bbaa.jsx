
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {StateContexts} from "$/utils/context"
import {Box as RadixThemesBox,Text as RadixThemesText} from "@radix-ui/themes"
import {jsx} from "@emotion/react"






export const Foreach_comp_dd76a22272d8e56e7de6bea3eb83bbaa = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        Array.prototype.map.call(reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.ai_words_rx_state_ ?? [],((item_rx_state_,index_e5cfe0f67d3f8de134346e070a43de7e)=>(jsx(RadixThemesBox,{css:({ ["padding"] : "0.6rem 0.875rem", ["background"] : "white", ["border"] : "1px solid #e2e0db", ["borderRadius"] : "0.5rem", ["transition"] : "all 180ms ease", ["boxShadow"] : "0 1px 3px rgba(0,0,0,0.04)", ["&:hover"] : ({ ["borderColor"] : "rgba(1,105,111,0.3)", ["background"] : "rgba(1,105,111,0.04)", ["boxShadow"] : "0 2px 8px rgba(1,105,111,0.1)" }) }),key:index_e5cfe0f67d3f8de134346e070a43de7e},jsx(RadixThemesText,{as:"p",css:({ ["fontSize"] : "0.875rem", ["color"] : "#28251d", ["lineHeight"] : "1.5", ["fontWeight"] : "500" })},item_rx_state_?.["words"])))))
    )
});
