
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {StateContexts} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_c6830495b7722bf9600cfa5b264c61b6 = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state)



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["width"] : "100%" }),disabled:reflex___state____state__learnspot___state___auth____auth_state.loading_rx_state_,size:"3",type:"submit"},children)
    )
});
