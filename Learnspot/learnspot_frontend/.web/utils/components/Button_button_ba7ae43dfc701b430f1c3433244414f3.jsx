
import {Fragment,memo,useCallback,useContext,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {StateContexts,addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_ba7ae43dfc701b430f1c3433244414f3 = memo(({children}) => {
    const on_click_d7b9229eac6d739898943650e720beba = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.handle_with_ai", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])
const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state)



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),loading:reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___practice____practice_state.practice_loading_rx_state_,onClick:on_click_d7b9229eac6d739898943650e720beba,size:"3",variant:"outline"},children)
    )
});
