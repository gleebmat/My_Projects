
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_7a8466d6eb0c74ef2e36979fa530afbf = memo(({children}) => {
    const on_click_39f08161aae812175d19251395ec6433 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.logout", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"gray",css:({ ["cursor"] : "pointer" }),onClick:on_click_39f08161aae812175d19251395ec6433,size:"2",variant:"soft"},children)
    )
});
