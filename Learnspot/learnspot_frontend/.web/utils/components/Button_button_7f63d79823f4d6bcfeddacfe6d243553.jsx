
import {Fragment,memo,useCallback,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {StateContexts,addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_7f63d79823f4d6bcfeddacfe6d243553 = memo(({children}) => {
    const on_click_c598e97ec436a3dd75ea3c2da6bd6d40 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.start_quiz", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])
const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),loading:reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.practice_loading_rx_state_,onClick:on_click_c598e97ec436a3dd75ea3c2da6bd6d40,size:"3"},children)
    )
});
