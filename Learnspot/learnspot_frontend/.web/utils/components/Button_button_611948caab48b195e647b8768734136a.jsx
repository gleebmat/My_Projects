
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_611948caab48b195e647b8768734136a = memo(({children}) => {
    const on_click_127b5b8bfa771ff2a55ab7263f0e3edd = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.load_ai_words", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),onClick:on_click_127b5b8bfa771ff2a55ab7263f0e3edd,size:"3",variant:"outline"},children)
    )
});
