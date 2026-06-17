
import {Fragment,memo,useCallback,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {StateContexts,addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_3d9e623991289ce4b56d00eb22003003 = memo(({children}) => {
    const on_click_dacbc72eb14d2cdd82e9ff360e63b64b = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.load_words", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])
const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),loading:reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.practice_loading_rx_state_,onClick:on_click_dacbc72eb14d2cdd82e9ff360e63b64b,size:"3",variant:"soft"},children)
    )
});
